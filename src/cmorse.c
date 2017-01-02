/*
	cmorse - simple text to Morse code converter
	Copyright (C) 2016	Jacek Wieczorek <mrjjot@gmail.com>

	This file is part of cmorse.

	Cmorse is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Cmorse is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "cmorse.h"

//Display version number
void version( int exitcode )
{
	fprintf( stderr, "cmorse " VERSION "\n\n\r" );
	fprintf( stderr,
		"This program is distributed in the hope that it will be useful,\n\r"
		"but WITHOUT ANY WARRANTY; without even the implied warranty of\n\r"
		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\r"
		"GNU General Public License for more details.\n\r" );
	exit( exitcode );
}

//Display help message
void help( int exitcode )
{
	fprintf( stderr, "cmorse " VERSION "\n\n\r" );
	fprintf( stderr,
		"This program is distributed in the hope that it will be useful,\n\r"
		"but WITHOUT ANY WARRANTY; without even the implied warranty of\n\r"
		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\r"
		"GNU General Public License for more details.\n\n\r" );

	fprintf( stderr, "Usage: cmorse [OPTIONS]\n\r" );
	fprintf( stderr, "\t -a - append data to file instead of overwriting it\n\r" );
	fprintf( stderr, "\t -d - decrypt (from Morse to text)\n\r" );
	fprintf( stderr, "\t -h - show this help message\n\r" );
	fprintf( stderr, "\t -i <filename> - input file name (if not specified reads from stdin)\n\r" );
	fprintf( stderr, "\t -o <filename> - output file name (if not specified writes to stdout)\n\r" );
	fprintf( stderr, "\t -p - disable automatic prosign encryption\n\r" );
	fprintf( stderr, "\t -u - output uppercase text when decrypting\n\r" );
	fprintf( stderr, "\t -v - show version number\n\r" );
	fprintf( stderr, "\nSee also: `man cmorse`\n\r" );
	exit( exitcode );
}

//Return pointer to an allocated part of memory containing string read from f
char *afgets( FILE *f )
{
	const size_t step = 1; //Amount of characters, that will be appended to string, each time we run out of space

	size_t i = 0, len = 8; //Current character index and initial str length
	char *str; //String
	int c; //Current character (int is better than char, ya know...)

	//Allocate space for first few characters
	if ( ( str = (char *) malloc( len ) ) == NULL ) return NULL;
	do //Repeat until c is 0, or realloc error occured
	{
		c = getc( f ); //Read single character
		//If current character pointer reaches end of string, allocate more memory
		if ( i >= len )
			if ( ( str = (char *) realloc( str, ( len += step ) ) ) == NULL ) return NULL;
		//Is character EOT or EOF? If so, set it to 0 to exit loop
		if ( c == 4 || c == EOF )
			c = 0;
		str[i++] = c; //Write character to array, and increment i
	}
	while ( c != 0 );
	return str;
}

//Text -> Morse conversion
void encrypt( FILE *outputfile, char *str, size_t len )
{
	unsigned char j, badc;
	size_t i;

	//Read characters from input file
	for ( i = 0; i < len; i++ )
	{
		badc = 1;

		//Iterate through pseudo-hash, looking for matches
		for ( j = 0; j < SUPPORTED_CHARACTERS && badc; j++ )
		{
			if ( tolower( str[i] ) == morse[j][0][0] )
			{
				if ( ( str[i] == '\n' || str[i] == '\r' ) && flags & FLAG_NOPROSIGNS )
				{
					badc = 0;
					continue;
				}

				//If next character is space, do not add additional one
				fprintf( outputfile, "%s%s", morse[j][1], ( i + 1 < len ) ? ( ( str[i + 1] == ' ' ) ? "" : " " ) : "" );
				badc = 0;
			}
		}

		//If no matches were found, throw a warning
		if ( badc ) fprintf( stderr, "cmorse: unsupported character (ASCII only) - %c (0x%x) - c%ld\n\r", str[i], str[i], (long) i );
	}
}

//Morse -> Text conversion
void decrypt( FILE *outputfile, char *str, size_t len )
{
	char *morsechar = (char *) malloc( 1 );
	unsigned char badc, j, spaces = 0;
	size_t i, charend = 0;

	for ( i = 0; i < len; i++ )
	{
		badc = 1;

		//Ignore newlines etc.
		if ( str[i] == '\n' || str[i] == '\r' || str[i] == '\t' )
			continue;

		//Is space?
		if ( str[i] == ' ' )
		{
			spaces++;
			continue;
		}
		else
		{
			for ( j = 0; j < ( spaces >> 1 ); j++ ) fprintf( outputfile, " " );
			spaces = 0;
		}

		//Look for next meaningful character
		charend = i;
		while ( str[charend] != ' ' && str[charend] != '\0' && str[charend] != '\n' && str[charend] != '\r' && str[charend] != '\t' && charend < len )
			charend++;

		//Copy morse code to temporary array
		morsechar = (char *) realloc( morsechar, charend - i + 1 );
		memcpy( morsechar, str + i, charend - i );
		morsechar[charend - i] = 0;
		for ( j = 0; j < SUPPORTED_CHARACTERS; j++ )
		{
			if ( !strcmp( morsechar, morse[j][1] ) )
			{
				if ( ( morse[j][0][0] == '\n' || morse[j][0][0] == '\r' ) && flags & FLAG_NOPROSIGNS )
				{
					badc = 0;
					continue;
				}

				fprintf( outputfile, "%c", ( flags & FLAG_UPPERCASE ) ? toupper( morse[j][0][0] ) : morse[j][0][0] );
				badc = 0;
			}
		}

		if ( badc ) fprintf( stderr, "cmorse: unsupported Morse code - '%s' - c%ld\n\r", morsechar, (long) i );

		i = charend - 1;
	}

	free( morsechar );
}

int main( int argc, char **argv )
{
	unsigned char i;
	char *inputstr = NULL, *inputfilename = NULL, *outputfilename = NULL, argparsed = 0;
	FILE *inputfile = NULL, *outputfile = NULL;
	size_t inputstrlen;

	//Search argv for supported arguments
	for ( i = 1; i < argc; i++ )
	{
		//Argument is assument to be not parsed as default
		argparsed = 0;

		//Show help message
		if ( !strcmp( argv[i], "-h" ) || !strcmp( argv[i], "--help" ) )
		{
			argparsed = 1;
			help( 0 );
		}

		//Show version number
		if ( !strcmp( argv[i], "-v" ) || !strcmp( argv[i], "--version" ) )
		{
			argparsed = 1;
			version( 0 );
		}

		//Decrpyt morse message
		if ( !strcmp( argv[i], "-d" ) || !strcmp( argv[i], "--decrypt" ) )
		{
			argparsed = 1;
			flags |= FLAG_DECRYPT;
		}

		//Output uppercase letters
		if ( !strcmp( argv[i], "-u" ) || !strcmp( argv[i], "--uppercase" ) )
		{
			argparsed = 1;
			flags |= FLAG_UPPERCASE;
		}

		//Output uppercase letters
		if ( !strcmp( argv[i], "-p" ) || !strcmp( argv[i], "--prosignsdisabled" ) )
		{
			argparsed = 1;
			flags |= FLAG_NOPROSIGNS;
		}

		//Append data
		if ( !strcmp( argv[i], "-a" ) || !strcmp( argv[i], "--append" ) )
		{
			argparsed = 1;
			flags |= FLAG_APPEND;
		}

		//Specify input file
		if ( !strcmp( argv[i], "-i" ) || !strcmp( argv[i], "--input" ) )
		{
			argparsed = 1;
			if ( i + 1 < argc )
			{
				inputfilename = argv[++i];
			}
			else
			{
				fprintf( stderr, "cmorse: missing input file name.\nTry -h option to get more information.\n\r" );
				exit( 1 );
			}
		}

		//Specify output file
		if ( !strcmp( argv[i], "-o" ) || !strcmp( argv[i], "--output" ) )
		{
			argparsed = 1;
			if ( i + 1 < argc )
				outputfilename = argv[++i];
			else
			{
				fprintf( stderr, "cmorse: missing output file name.\nTry -h option to get more information.\n\r" );
				exit( 1 );
			}
		}

		//Throw error if argument is unexpected
		if ( !argparsed )
		{
			fprintf( stderr, "cmorse: unknown option: %s\n\r", argv[i] );
			help( 1 );
		}
	}

	//Open input file
	if ( inputfilename == NULL ) inputfile = stdin;
	else if ( ( inputfile = fopen( inputfilename, "r" ) ) == NULL  )
	{
		fprintf( stderr, "cmorse: unable to open input file.\nTry -h option to get more information.\n\r" );
		exit( 1 );
	}

	DEBUG( "%d", inputfilename );
	inputstr = afgets( inputfile );
	inputstrlen = strlen( inputstr );

	//Close input file
	if ( inputfile != stdin ) fclose( inputfile );
	else if ( outputfilename == NULL ) printf( "\n" );

	//Open outputfile
	if ( outputfilename == NULL ) outputfile = stdout;
	else if ( ( outputfile = fopen( outputfilename, ( flags & FLAG_APPEND ) ? "a" : "w" ) ) == NULL )
	{
		fprintf( stderr, "cmorse: unable to open output file.\nTry -h option to get more information.\n\r" );
		exit( 1 );
	}

	//Encrypt or decrypt file
	if ( flags & FLAG_DECRYPT )
		decrypt( outputfile, inputstr, inputstrlen );
	else
		encrypt( outputfile, inputstr, inputstrlen );

	//Print empty line or close input file
	if ( outputfile == stdout ) printf( "\n\r" );
	else fclose( outputfile );

	free( inputstr );

	return 0;
}
