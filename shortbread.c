#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * next_token(char *s, char const del)
{
	static char *olds;
	if (s == NULL)
		s = olds;
	while (*s == del)
		s++;
	if (*s == '\0') {
		olds = s;
		return NULL;
	}
	char *token = s;
	while (*s != '\0' && *(++s) != del);
	if (*s == del) {
		*s = '\0';
		olds = s+1;
	} else
		olds = s;
	return token;
}

int main(int argc, char** argv)
{
	char *home = getenv("HOME");
	size_t l_home = strlen(home);
	char *cwd = strdup(argc > 1 ? argv[1] : getenv("PWD"));
	// is cwd a subdirectory of home ?
	bool sub_home = memcmp(home, cwd, l_home) == 0;
	// number of directories below root/home
	int depth = 0;
	// index of path after base dir
	char *subpath = cwd + (sub_home ? l_home : 0);
	for (char *i = subpath; *i; i++)
		if (*i == '/')
			++depth;
	// print prefix
	if (sub_home)
		printf("~");
	if (depth == 1)
		printf("%s", subpath);
	if (depth <= 1) {
		printf("\n");
		return 0;
	}
	char *short_dirs = subpath;
	char *short_dirs_i = short_dirs;
	char *dir = next_token(subpath, '/');
	int i = 0;
	while (i++ < depth-1 && dir != NULL) {
		*(short_dirs_i++) = '/';
	add_char:
		*(short_dirs_i++) = *dir;
		// print hidden and special (.|..) paths unambiguously
		if (*dir == '.' && *(++dir) != '\0')
			goto add_char;
		if (*(dir+1) >> 7) {
			dir++;
			goto add_char;
		}
		dir = next_token(NULL, '/');
	}
	*short_dirs_i = '\0';
	printf("%s/%s\n", short_dirs, dir);
	free(cwd);
}
