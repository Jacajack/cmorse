# cmorse
[![The MIT License](https://img.shields.io/badge/license-MIT-orange.svg?style=flat-square)](http://opensource.org/licenses/MIT)
[![Travis CI](https://img.shields.io/travis/Jacajack/cmorse.svg?style=flat-square)](https://travis-ci.org/Jacajack/cmorse)

`cmorse` is a simple text to Morse code converter.

[Cmorse on launchpad...](https://launchpad.net/cmorse)

## Installing cmorse
 - Add PPA to your system - `sudo add-apt-repository ppa:mrjjot/cmorse`
 - Update software lists - `sudo apt-get update`
 - Install `cmorse` package - `sudo apt-get install cmorse`


## Fine, but how do I use it?
To invoke cmorse simply run `cmorse -i example.txt`, where `example.txt` is file you want to convert into Morse code.
Encoded data will be outputted through `stdout`. You can redirect it to another file like this: `cmorse -i example.txt > encoded.txt`.

If you want to see more options use `cmorse -h` to display help message.

## Building cmorse
 - `make all`
 - `make install`

To uninstall run `make uninstall`
