/* This is simple text-Morse's alphabet converter writen in C */
/* By Jacajack (Jacek Wieczorek) <mrjjot@gmail.com> 2016 */

#include "cmorse.h"

//Display version number
void version( int exitcode )
{
	fprintf( stderr, "cmorse %s\n\r", VERSION );
	exit( exitcode );
}

//Display help message
void help( int exitcode )
{
	fprintf( stderr, "cmorse %s\n\r", VERSION );
	fprintf( stderr, "Usage: cmorse [OPTIONS] input-file\n\r" );
	fprintf( stderr, "\t -h - show this help message\n\r" );
	fprintf( stderr, "\t -v - show version number\n\r" );
	fprintf( stderr, "\t -d - decrypt (from Morse to text) (risky!)\n\r" );
	fprintf( stderr, "\t -u - output uppercase letter when decrypting\n\r" );
	exit( exitcode );
}

//Text -> Morse conversion
void encrypt( char *str, size_t len )
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
				//If next character is space, do not add additional one
				printf( "%s%s", morse[j][1], ( i + 1 < len ) ? ( ( str[i + 1] == ' ' ) ? "" : " " ) : "" );
				badc = 0;
			}
		}

		//If no matches were found, throw a warning
		if ( badc ) fprintf( stderr, "cmorse: unsupported character (ASCII only) - %c (0x%x) - c%ld\n\r", str[i], str[i], i );
	}
}

//Morse -> Text conversion
void decrypt( char *str, size_t len )
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
			for ( j = 0; j < ( spaces >> 1 ); j++ ) printf( " " );
			spaces = 0;
		}

		charend = i;
		while ( str[charend] != ' ' && str[charend] != '\0' && str[charend] != '\n' && str[charend] != '\r' && str[charend] != '\t' && charend < len )
			charend++;

		morsechar = (char *) realloc( morsechar, charend - i + 1 );
		memcpy( morsechar, str + i, charend - i );
		morsechar[charend - i] = 0;
		//printf( "%s ", morsechar );
		for ( j = 0; j < SUPPORTED_CHARACTERS; j++ )
		{
			if ( !strcmp( morsechar, morse[j][1] ) )
			{
				printf( "%c", ( flags & FLAG_UPPERCASE ) ? toupper( morse[j][0][0] ) : morse[j][0][0] );
				badc = 0;
			}
		}

		if ( badc ) fprintf( stderr, "cmorse: unsupported Morse code - '%s' - c%ld\n\r", morsechar, i );

		i = charend - 1;
	}

	free( morsechar );
}

int main( int argc, char **argv )
{
	unsigned char i;
	char *inputstr;
	size_t inputfilelen, inputstrlen;
	FILE *inputfile;

	//If ran without arguments
	if ( argc == 1 )
		help( 1 );

	//Search argv for supported arguments
	for ( i = 0; i < argc; i++ )
	{
		//Show help message
		if ( !strcmp( argv[i], "-h" ) || !strcmp( argv[i], "--help" ) )
			help( 0 );

		//Show version number
		if ( !strcmp( argv[i], "-v" ) || !strcmp( argv[i], "--version" ) )
			version( 0 );

		//Decrpyt morse message
		if ( !strcmp( argv[i], "-d" ) || !strcmp( argv[i], "--decrypt" ) )
			flags |= FLAG_DECRYPT;

		//Output uppercase letters
		if ( !strcmp( argv[i], "-u" ) || !strcmp( argv[i], "--uppercase" ) )
			flags |= FLAG_UPPERCASE;
	}

	//Open input file
	if ( ( inputfile = fopen( argv[argc - 1], "r" ) ) == NULL )
	{
		fprintf( stderr, "cmorse: unable to open input file.\nTry -h option to get more information.\n\r" );
		exit( 1 );
	}

	//Loading whole file to memory, instead of streaming may be a not good idea, but this solution, makes managing ' ' easier

	//Get file length
	fseek( inputfile, 0, SEEK_END );
	inputfilelen = ftell( inputfile );
	rewind( inputfile );

	//Allocate memory
	if ( ( inputstr = (char *) malloc( inputfilelen + 1 ) ) == NULL )
	{
		fprintf( stderr, "cmorse: memory allocation error.\n\r" );
		exit( 1 );
	}

	//Read input file
	while ( ( inputstr[ftell( inputfile )] = getc( inputfile ) ) != EOF );
	inputstr[inputfilelen] = 0;
	inputstrlen = strlen( inputstr );

	fclose( inputfile );

	//Encrypt or decrypt file
	if ( flags & FLAG_DECRYPT )
		decrypt( inputstr, inputstrlen );
	else
		encrypt( inputstr, inputstrlen );

	free( inputstr );
	printf( "\n\r" );

	return 0;
}
