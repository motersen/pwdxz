CC=gcc
DESTDIR=$(HOME)
CFLAGS=-O3 -Wall

pwdxz: pwdxz.c
	$(CC) $(CFLAGS) -o pwdxz pwdxz.c

install: pwdxz
	strip pwdxz
	install -Dm755 pwdxz $(DESTDIR)/bin/pwdxz

uninstall:
	rm -rf $(DESTDIR)/bin/pwdxz

clean:
	rm -rf pwdxz
