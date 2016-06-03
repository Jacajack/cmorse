#include <stdio.h>
#include <error.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>
#include <locale.h>

#ifndef DEBUG_ENABLED
#define DEBUG_ENABLED 0
#else
#define DEBUG_OUT printf
#endif
#include "debug.h"

#define VERSION "v1.1-dev"

#define FLAG_DECRYPT ( 1 << 0 )
#define FLAG_UPPERCASE ( 1 << 1 )
#define FLAG_NOPROSIGNS ( 1 << 2 )
#define FLAG_APPEND ( 1 << 3 )

unsigned char flags = 0;


#define CHARSET_LENGTH 60 //Maximum character set length
#define MORSE_CODE_LENGTH 8 //Maximum length of single morse code
#include "./charsets/default.h"

//Current character set
wchar_t ( *morse )[2][MORSE_CODE_LENGTH] ;
