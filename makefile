CC = gcc
CFLAGS = -Wall

all: clean FORCE src/cmorse.c include/cmorse.h include/debug.h
	$(CC) $(CFLAGS) -o bin/cmorse src/cmorse.c

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
