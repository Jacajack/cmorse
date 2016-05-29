#include <stdio.h>
#include <error.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>
#include <string.h>

#ifndef DEBUG_ENABLED
#define DEBUG_ENABLED 0
#else
#define DEBUG_OUT printf
#endif
#include "debug.h"


#define VERSION "v1.1"
#define SUPPORTED_CHARACTERS 57

#define FLAG_DECRYPT ( 1 << 0 )
#define FLAG_UPPERCASE ( 1 << 1 )
#define FLAG_NOPROSIGNS ( 1 << 2 )

unsigned char flags = 0;

const char morse[SUPPORTED_CHARACTERS][2][8] =
{
	{"a", ".-"},
	{"b", "-..."},
	{"c", "-.-."},
	{"d", "-.."},
	{"e", "."},
	{"f", "..-."},
	{"g", "--."},
	{"h", "...."},
	{"i", ".."},
	{"j", ".---"},
	{"k", "-.-"},
	{"l", ".-.."},
	{"m", "--"},
	{"n", "-."},
	{"o", "---"},
	{"p", ".--."},
	{"q", "--.-"},
	{"r", ".-."},
	{"s", "..."},
	{"t", "-"},
	{"u", "..-"},
	{"v", "...-"},
	{"w", ".--"},
	{"x", "-..-"},
	{"y", "-.--"},
	{"z", "--.."},

	{"0", "-----"},
	{"1", ".----"},
	{"2", "..---"},
	{"3", "...--"},
	{"4", "....-"},
	{"5", "....."},
	{"6", "-...."},
	{"7", "--..."},
	{"8", "---.."},
	{"9", "----."},

	{".", ".-.-.-"},
	{",", "--..--"},
	{":", "---..."},
	{";", "-.-.-."},
	{"?", "..--.."},
	{"\'", ".----."},
	{"!", "-.-.--"},
	{"+", ".-.-."},
	{"-", "-....-"},
	{"/", "-..-."},
	{"(", "-.--."},
	{")", "-.--.-"},
	{"\"", ".-..-."},
	{"@", ".--.-."},
	{"$", "...-..-"},
	{"=", "-...-"},
	{"&", ".-..."},
	{"_", "..--.-"},

	{" ", " "},

	//Prosigns (in fact, unsure how to implement correctly)
	{"\n", ".-.-" },
	{"\r", ".-.-" }
};
