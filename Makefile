CC=gcc
DESTDIR=$(HOME)
CFLAGS=-O3 -Wall

sb: shortbread.c
	$(CC) $(CFLAGS) -o sb shortbread.c

install: sb
	strip sb
	install -Dm755 sb $(DESTDIR)/bin/sb

uninstall:
	rm -rf $(DESTDIR)/bin/sb

clean:
	rm -rf sb
