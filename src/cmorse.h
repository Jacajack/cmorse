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


#define VERSION "v1.1b"
#define SUPPORTED_CHARACTERS 57

#define FLAG_DECRYPT ( 1 << 0 )
#define FLAG_UPPERCASE ( 1 << 1 )
#define FLAG_NOPROSIGNS ( 1 << 2 )
#define FLAG_APPEND ( 1 << 3 )

unsigned char flags = 0;

const char morse[SUPPORTED_CHARACTERS][2][8] =
{
	{" ", " "},

	{"e", "."},
	{"t", "-"},
	{"a", ".-"},
	{"o", "---"},
	{"i", ".."},
	{"n", "-."},
	{"s", "..."},
	{"h", "...."},
	{"r", ".-."},
	{"d", "-.."},
	{"l", ".-.."},
	{"c", "-.-."},
	{"u", "..-"},
	{"m", "--"},
	{"w", ".--"},
	{"f", "..-."},
	{"g", "--."},
	{"y", "-.--"},
	{"p", ".--."},
	{"b", "-..."},
	{"v", "...-"},
	{"k", "-.-"},
	{"j", ".---"},
	{"x", "-..-"},
	{"q", "--.-"},
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


	//Prosigns (in fact, unsure how to implement correctly)
	{"\n", ".-.-" },
	{"\r", "" } //Carriage return is ignored since it doubled line spacing
};
