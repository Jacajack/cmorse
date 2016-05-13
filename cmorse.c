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
void encrypt( char *str )
{
	unsigned char j, badc;
	size_t i, len = strlen( str );

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
		if ( badc ) fprintf( stderr, "cmorse: unsupported character (ASCII only) - %c - c%ld\n\r", str[i], i );
	}
}

//Morse -> Text conversion
void decrypt( char *str )
{

}

int main( int argc, char **argv )
{
	unsigned char i, flags;
	char *inputstr;
	size_t inputfilelen;
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

	//Loading whole file to memory, instead of streaming may be a not good idea, but this solution, makes managing ' ' easier

	//Get file length
	fseek( inputfile, 0, SEEK_END );
	inputfilelen = ftell( inputfile );
	rewind( inputfile );

	//Allocate memory
	if ( ( inputstr = (char *) malloc( inputfilelen + 1) ) == NULL )
	{
		fprintf( stderr, "cmorse: memory allocation error.\n\r" );
		exit( 1 );
	}

	//Read input file
	while ( ( inputstr[ftell( inputfile )] = getc( inputfile ) ) != EOF );
	inputstr[inputfilelen] = 0;

	fclose( inputfile );

	//Encrypt or decrypt file
	if ( flags & FLAG_DECRYPT )
		decrypt( inputstr );
	else
		encrypt( inputstr );

	free( inputstr );
	printf( "\n\r" );

	return 0;
}
