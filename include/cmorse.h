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
#define SUPPORTED_CHARACTERS 57

#define FLAG_DECRYPT ( 1 << 0 )
#define FLAG_UPPERCASE ( 1 << 1 )
#define FLAG_NOPROSIGNS ( 1 << 2 )
#define FLAG_APPEND ( 1 << 3 )

unsigned char flags = 0;

const wchar_t morse[SUPPORTED_CHARACTERS][2][8] =
{
	{L"a", L".-"},
	{L"b", L"-..."},
	{L"c", L"-.-."},
	{L"d", L"-.."},
	{L"e", L"."},
	{L"f", L"..-."},
	{L"g", L"--."},
	{L"h", L"...."},
	{L"i", L".."},
	{L"j", L".---"},
	{L"k", L"-.-"},
	{L"l", L".-.."},
	{L"m", L"--"},
	{L"n", L"-."},
	{L"o", L"---"},
	{L"p", L".--."},
	{L"q", L"--.-"},
	{L"r", L".-."},
	{L"s", L"..."},
	{L"t", L"-"},
	{L"u", L"..-"},
	{L"v", L"...-"},
	{L"w", L".--"},
	{L"x", L"-..-"},
	{L"y", L"-.--"},
	{L"z", L"--.."},

	{L"0", L"-----"},
	{L"1", L".----"},
	{L"2", L"..---"},
	{L"3", L"...--"},
	{L"4", L"....-"},
	{L"5", L"....."},
	{L"6", L"-...."},
	{L"7", L"--..."},
	{L"8", L"---.."},
	{L"9", L"----."},

	{L".", L".-.-.-"},
	{L",", L"--..--"},
	{L":", L"---..."},
	{L";", L"-.-.-."},
	{L"?", L"..--.."},
	{L"\'", L".----."},
	{L"!", L"-.-.--"},
	{L"+", L".-.-."},
	{L"-", L"-....-"},
	{L"/", L"-..-."},
	{L"(", L"-.--."},
	{L")", L"-.--.-"},
	{L"\"", L".-..-."},
	{L"@", L".--.-."},
	{L"$", L"...-..-"},
	{L"=", L"-...-"},
	{L"&", L".-..."},
	{L"_", L"..--.-"},

	{L" ", L" "},

	//Prosigns (in fact, unsure how to implement correctly)
	{L"\n", L".-.-" },
	{L"\r", L"" } //Carriage return is ignored since it doubled line spacing
};
