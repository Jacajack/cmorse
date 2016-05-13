# cmorse
[![The MIT License](https://img.shields.io/badge/license-MIT-orange.svg?style=flat-square)](http://opensource.org/licenses/MIT)
[![Travis CI](https://img.shields.io/travis/Jacajack/cmorse.svg?style=flat-square)](https://travis-ci.org/Jacajack/cmorse)

`cmorse` is a simple text to Morse code converter.

## Installing cmorse
1. `make all`
2. `make install`

To uninstall - `make uninstall`

## Using cmorse
To invoke cmorse simply run `cmorse example.txt`, where `example.txt` is file you want to convert into Morse code.
Encoded data will be outputted through `stdout`. You can redirect it to another file like this: `cmorse example.txt > encoded.txt`.

If you want to see more options use `cmorse -h` to display help message.
