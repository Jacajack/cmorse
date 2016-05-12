$CC = gcc

all: clean FORCE cmorse.c cmorse.h
	gcc -Wall -o bin/cmorse cmorse.c

install:
	-mkdir -p $(DESTDIR)/usr
	-mkdir -p $(DESTDIR)/usr/bin
	cp -R bin/cmorse $(DESTDIR)/usr/bin

uninstall:
	-rm -rf $(DESTDIR)/usr/bin/cmorse

FORCE:
	-mkdir bin

clean:
	-rm -rf bin
