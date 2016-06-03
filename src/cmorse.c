/* This is simple text-Morse's alphabet converter writen in C */
/* By Jacajack (Jacek Wieczorek) <mrjjot@gmail.com> 2016 */

#include "../include/cmorse.h"

//Display version number
void version( int exitcode )
{
	fprintf( stderr, "cmorse " VERSION "\n\r" );
	exit( exitcode );
}

//Display help message
void help( int exitcode )
{
	fprintf( stderr, "cmorse " VERSION "\n\r" );
	fprintf( stderr, "Usage: cmorse [OPTIONS]\n\r" );
	fprintf( stderr, "\t -a - append data to file instead of overwriting it\n\r" );
	fprintf( stderr, "\t -c - select morse code character set\n\r" );
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
wchar_t *afwgets( FILE *f )
{
    const size_t step = 1; //Amount of characters, that will be appended to string, each time we run out of space

    size_t i = 0, len = 8; //Current character index and initial str length
    wchar_t *str, c; //String pointer and single character

    //Allocate space for first few characters
    if ( ( str = (wchar_t *) malloc( len * sizeof( wchar_t ) ) ) == NULL ) return NULL;
    do //Repeat until c is 0, or realloc error occured
    {
        c = getwc( f ); //Read single character
		DEBUG( "%d", c );
        //If current character pointer reaches end of string, allocate more memory
        if ( i >= len )
            if ( ( str = (wchar_t *) realloc( str, ( len += step ) * sizeof( wchar_t ) ) ) == NULL ) return NULL;
        //Is character EOT, EOF? If so, set it to 0 to exit loop
        if ( c == 4 || c == (wchar_t) WEOF )
            c = 0;
        str[i++] = c; //Write character to array, and increment i
    }
    while ( c != 0 );
    return str;
}

//Text -> Morse conversion
void encrypt( FILE *outputfile, wchar_t *str, size_t len )
{
	unsigned char j, badc;
	size_t i;

	//Read characters from input file
	for ( i = 0; i < len; i++ )
	{
		badc = 1;
		DEBUG( "%d", str[i] );

		//Iterate through pseudo-hash, looking for matches
		for ( j = 0; j < CHARSET_LENGTH && badc; j++ )
		{
			if ( (wchar_t) towlower( str[i] ) == charset[j][0][0] )
			{
				//DEBUG( "%c", (wint_t) str[i] );
				//DEBUG( "%S", morse[j][1] );

				if ( ( str[i] == L'\n' || str[i] == L'\r' ) && flags & FLAG_NOPROSIGNS )
				{
					badc = 0;
					continue;
				}

				//If next character is space, do not add additional one
				fprintf( outputfile, "%S%S", charset[j][1], ( i + 1 < len ) ? ( ( str[i + 1] == L' ' ) ? L"" : L" " ) : L"" );
				badc = 0;
			}
		}

		//If no matches were found, throw a warning
		if ( badc ) fprintf( stderr, "cmorse: unsupported character - %C (0x%x) - c%ld\n\r", (wint_t) str[i], (unsigned int) str[i], (long) i );
	}
}

//Morse -> Text conversion
void decrypt( FILE *outputfile, wchar_t *str, size_t len )
{
	wchar_t *morsechar = (wchar_t *) malloc( sizeof( wchar_t ) );
	unsigned char badc, j, spaces = 0;
	size_t i, charend = 0;

	for ( i = 0; i < len; i++ )
	{
		badc = 1;

		//Ignore newlines etc.
		if ( str[i] == L'\n' || str[i] == L'\r' || str[i] == L'\t' )
			continue;

		//Is space?
		if ( str[i] == L' ' )
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
		while ( str[charend] != L' ' && str[charend] != L'\0' && str[charend] != L'\n' && str[charend] != L'\r' && str[charend] != L'\t' && charend < len )
			charend++;

		//Copy morse code to temporary array
		morsechar = (wchar_t *) realloc( morsechar, ( charend - i + 1 ) * sizeof( wchar_t ) );
		memcpy( morsechar, str + i, ( charend - i ) * sizeof( wchar_t ) );
		morsechar[charend - i] = 0;
		for ( j = 0; j < CHARSET_LENGTH; j++ )
		{
			if ( !wcscmp( morsechar, charset[j][1] ) )
			{
				if ( ( charset[j][0][0] == L'\n' || charset[j][0][0] == L'\r' ) && flags & FLAG_NOPROSIGNS )
				{
					badc = 0;
					continue;
				}

				fprintf( outputfile, "%C", ( flags & FLAG_UPPERCASE ) ? towupper( charset[j][0][0] ) : (wint_t) charset[j][0][0] );
				badc = 0;
			}
		}

		if ( badc ) fprintf( stderr, "cmorse: unsupported Morse code - '%S' - c%ld\n\r", morsechar, (long) i );

		i = charend - 1;
	}

	free( morsechar );
}

int main( int argc, char **argv )
{
	unsigned char i;
	wchar_t *inputstr = NULL;
	char *inputfilename = NULL, *outputfilename = NULL, *charsetname = NULL, argparsed = 0;
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

		//Specify charset
		if ( !strcmp( argv[i], "-c" ) || !strcmp( argv[i], "--charset" ) )
		{
			argparsed = 1;
			if ( i + 1 < argc )
			{
				charsetname = argv[i++ + 1];
			}
			else
			{
				fprintf( stderr, "cmorse: missing character set name.\nTry -h option to get more information.\n\r" );
				exit( 1 );
			}
		}

		//Specify input file
		if ( !strcmp( argv[i], "-i" ) || !strcmp( argv[i], "--input" ) )
		{
			argparsed = 1;
			if ( i + 1 < argc )
			{
				inputfilename = argv[i++ + 1];
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
				outputfilename = argv[i++ + 1];
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

	//Set locale
	setlocale( LC_ALL, "" );

	//Select character set
	if ( charsetname == NULL || !strcmp( charsetname, "default" ) ) //Default character set
	{
		charset = charset_default;
	}
	else //Unknown character set
	{
		fprintf( stderr, "cmorse: unknown character set.\nTry -h option to get more information.\n\r" );
		exit( 1 );
	}

	//Open input file
	if ( inputfilename == NULL ) inputfile = stdin;
	else if ( ( inputfile = fopen( inputfilename, "rb" ) ) == NULL  )
	{
		fprintf( stderr, "cmorse: unable to open input file.\nTry -h option to get more information.\n\r" );
		exit( 1 );
	}

	DEBUG( "%s", inputfilename );
	inputstr = afwgets( inputfile );
	inputstrlen = wcslen( inputstr );
	DEBUG( "%d", inputstrlen );

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
