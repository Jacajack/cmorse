# cmorse 1 "6th December 2016" "v1.1-3"

##NAME
cmorse - text to Morse code converter (and vice versa)

##SYNOPSIS
cmorse [**-a**] [**-d**] [**-h**] [**-i** *filename*] [**-o** *filename*] [**-p**] [**-u**] [**-v**]

##DESCRIPTION
Coverts Morse code to text, or vice versa. Currently, only ASCII characters are supported.
If input file is not specified, cmorse will read stdin, until EOF, or EOT character occurs.
Similarly, if output file is not specified, cmorse will write output to stdout.
If **-a** option is not set, cmorse is going to **overwrite output file content**!

###Morse code format
Morse code is written as lines, dots and spaces.
There is one space between each two letter in a word, and words are separated by two spaces.
Normally, all characters are outputted lowercase (unless -p option is used).
Also, cmorse does not guarantee that line spacing will be exactly the same after encoding and decoding.

##OPTIONS
**-a**, **--append** - append data to file instead of overwriting it

**-d**, **--decode** - decode from Morse code to text file (assumes input file is in Morse code format)

**-h**, **--help** - display a help message

**-i**, **--input** *filename* - specifies input file name. Given file should not contain any non-ASCII characters, otherwise they won't be encrypted and cmorse will throw errors.

**-o**, **--output** *filename* - specifies output file name

**-p**, **--noprosigns** - do not change special characters (new line, etc.) to Morse prosigns (other Morse code applications may not handle them way cmorse does)

**-u**, **--uppercase** - output uppercase letters when decoding

**-v**, **--version** - display a version information


##EXAMPLES
*Recommended way of writing to files:*
	cmorse -i testfile2.txt -o output2.morse
	cmorse -d -i output2.morse -o output2.txt

*The second way:*
	cmorse -i testfile.txt > output.morse
	cmorse -d -i output.morse > output.txt

##BUGS
There are no known bugs yet, if you find some, please report them here:
https://github.com/Jacajack/cmorse/issues

##AUTHOR
Jacek Wieczorek <mrjjot@gmail.com>

Special thanks to **jconard3** for helping during the development.

##COPYRIGHT
Copyright (c) 2016 Jacek Wieczorek

The GNU General Public License v3.0
