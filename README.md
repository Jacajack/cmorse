**The development is currently put on hold - only necessary patches will be applied. No new features will be added, unless I find a new potential project maintainer. If you'd like to become one, please contact me.**

# cmorse
[![The GPL License](https://img.shields.io/badge/license-GPL-yellow.svg?style=flat-square)](https://opensource.org/licenses/GPL-3.0)
[![Travis CI](https://img.shields.io/travis/Jacajack/cmorse.svg?style=flat-square)](https://travis-ci.org/Jacajack/cmorse)

`cmorse` is a simple text to Morse code converter.

[Cmorse on launchpad...](https://launchpad.net/cmorse)

![Screenshot](http://i.imgur.com/2L7THtq.gif)
<br>*Screenshot of v1.1*

## Installing cmorse
 - Add PPA to your system - `sudo add-apt-repository ppa:mrjjot/cmorse`
 - Update software lists - `sudo apt-get update`
 - Install `cmorse` package - `sudo apt-get install cmorse`


## Usage
`cmorse [OPTIONS]`

Supported command line options:
 - `-a` / `--append` - Append to file instead of overwriting
 - `-d` / `--decrypt` - Convert from Morse code to regular text
 - `-h` / `--help` - Display help message
 - `-i` / `--input` - Specify input file in next argument
 - `-o` / `--output` - Specify input file in next argument
 - `-p` / `--prosginsdisabled` - Disable automatic prosign insertion (like `.-.-` instead of new line)
 - `-u` / `--uppercase` - Output uppercase text, when decrypting
 - `-v` / `--version` - Display software version number

For example, `cmorse -i example.txt -o example.morse` will encode `example.txt` and store Morse code in `example.morse`.
To reverse process use `cmorse -d -i example.morse -o decrypted.txt`.

When input file is not specified, `cmorse` will read `stdin` until `EOF` or `EOT` character occurs.
Same applies to output files - when not specified, `cmorse` will write to `stdout`.

## Building from source
 - Clone git repository - `git clone https://github.com/Jacajack/cmorse.git && cd cmorse`
 - Invoke makefile - `make all`
 - To install use `sudo make install`, and to uninstall - `sudo make uninstall`.

## Developing cmorse with Docker
 - Clone git repository - `git clone https://github.com/Jacajack/cmorse.git && cd cmorse`
 - Build docker image - `docker build -t cmorse .`
 - Run `cmorse` binary using docker container based on the cmorse image - `docker run -it cmorse cmorse`
