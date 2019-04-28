CC=gcc
DESTDIR=$(HOME)

pwdxz: pwdxz.c
	$(CC) -o pwdxz -O2 pwdxz.c

install: pwdxz
	install -Dm755 pwdxz $(DESTDIR)/bin/pwdxz

uninstall:
	rm -rf $(DESTDIR)/bin/pwdxz

clean:
	rm -rf pwdxz
