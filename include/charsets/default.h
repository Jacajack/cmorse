#ifndef CHARSET_LENGTH
#define CHARSET_LENGTH 60
#endif

#ifndef MORSE_CODE_LENGTH
#define MORSE_CODE_LENGTH 8
#endif

wchar_t morse_default[CHARSET_LENGTH][2][MORSE_CODE_LENGTH] =
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
