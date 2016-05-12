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
	fprintf( stderr, "\t -d - decrypt (from Morse to text) (not supported yet!)\n\r" );
	exit( exitcode );
}

//Text -> Morse conversion
void encrypt( FILE *f )
{
	unsigned char i, badc;
	wchar_t c;

	//Read characters from input file
	while ( ( c = getc( f ) ) != EOF )
	{
		badc = 1;

		//Iterate through pseudo-hash, looking for matches
		for ( i = 0; i < 52; i++ )
		{
			if ( tolower( c ) == (wchar_t) morse[i][0][0] )
			{
				printf( "%s ", morse[i][1] );
				badc = 0;
			}
		}

		//If no matches were found, throw a warning
		if ( badc ) fprintf( stderr, "cmorse: unsupported character (ASCII only) - %c - c%ld\n\r", c, ftell( f ) );
	}
}

//Morse -> Text conversion
void decrypt( FILE *f )
{

}

int main( int argc, char **argv )
{
	unsigned char i, flags;
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

		if ( !strcmp( argv[i], "-d" ) || !strcmp( argv[i], "--decrypt" ) )
			flags |= FLAG_DECRYPT;
	}

	//Open input file
	if ( ( inputfile = fopen( argv[argc - 1], "r" ) ) == NULL )
	{
		fprintf( stderr, "cmorse: unable to open input file.\nTry -h option to get more information.\n\r" );
		exit( 1 );
	}

	//Encrypt or decrypt file
	if ( flags & FLAG_DECRYPT )
		decrypt( inputfile );
	else
		encrypt( inputfile );

	fclose( inputfile );
	printf( "\n\r" );

	return 0;
}
