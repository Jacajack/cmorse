/* This is simple text-Morse's alphabet converter writen in C */
/* By Jacajack (Jacek Wieczorek) <mrjjot@gmail.com> 2016 */

#include "cmorse.h"

int main( int argc, char **argv )
{
	unsigned char i, badc;
	FILE *in;
	wchar_t c;

	if ( argc == 1 || argc > 2 )
	{
		fprintf( stderr, "%s: usage: %s input-file\n\r", argv[0], argv[0] );
		exit( 1 );
	}

	if ( ( in = fopen( argv[1], "r" ) ) == NULL )
	{
		fprintf( stderr, "%s: unable to open input file\n\r", argv[0] );
		exit( 1 );
	}

	while ( ( c = getc( in ) ) != EOF )
	{
		badc = 1;

		for ( i = 0; i < 52; i++ )
		{
			if ( tolower( c ) == (wchar_t) morse[i][0][0] )
			{
				printf( "%s ", morse[i][1] );
				badc = 0;
			}
		}

		if ( badc ) fprintf( stderr, "%s: unsupported character (ASCII only) - c%ld\n\r", argv[0], ftell( in ) );
	}

	fclose( in );
	printf( "\n\r" );
	return 0;
}
