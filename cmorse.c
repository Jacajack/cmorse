/* This is simple text-Morse's alphabet converter writen in C */
/* By Jacajack (Jacek Wieczorek) <mrjjot@gmail.com> 2016 */

#include "cmorse.h"

void version( int exitcode )
{
	//Display version number

	fprintf( stderr, "cmorse %s\n\r", VERSION );
	exit( exitcode );
}

void help( int exitcode )
{
	//Display help message

	fprintf( stderr, "cmorse %s\n\r", VERSION );
	fprintf( stderr, "Usage: cmorse [OPTIONS] input-file\n\r" );
	fprintf( stderr, "\t -h - show this help message\n\r" );
	fprintf( stderr, "\t -v - show version number\n\r" );
	fprintf( stderr, "\t -d - decrypt (from Morse to text) (not supported yet!)\n\r" );
	exit( exitcode );
}

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
		if ( badc ) fprintf( stderr, "cmorse: unsupported character (ASCII only) - c%ld\n\r", ftell( f ) );
	}
}

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
		if ( !strcmp( argv[i], "-h" ) )
			help( 0 );

		if ( !strcmp( argv[i], "-v" ) )
			version( 0 );

		if ( !strcmp( argv[i], "-d" ) )
			flags |= FLAG_DECRYPT;
	}

	//Open input file
	if ( ( inputfile = fopen( argv[argc - 1], "r" ) ) == NULL )
	{
		fprintf( stderr, "cmorse: unable to open input file\n\r" );
		help( 1 );
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
