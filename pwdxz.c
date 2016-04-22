#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	char *home = getenv("HOME");
	size_t l_home = strlen(home);
	char *cwd = argc > 1 ? argv[1] : getenv("PWD");
	// is cwd a subdirectory of home ?
	bool sub_home = memcmp(home, cwd, l_home) == 0;
	// number of directories below root/home
	int depth = 0;
	// index of last slash
	char *i_basename = cwd;
	// index of path after base dir
	char *i_midpath = cwd + (sub_home ? l_home : 0);
	for (char *i = i_midpath; *i; i++)
		if (*i == '/') {
			i_basename = i;
			++depth;
		}
	// print prefix
	if (sub_home)
		printf("~");
	if (depth == 1)
		printf("%s", i_midpath);
	if (depth <= 1)
		return 0;
	char *short_dirs = malloc(sizeof(char) * (2 * (depth - 1) + 1));
	for (char *i = i_midpath, *j = short_dirs; i < i_basename; i++)
		if (*i == '/') {
			*(j++) = '/';
			*(j++) = *(++i);
		}
	*(short_dirs + 2 * (depth - 1)) = '\0';
	printf("%s%s\n", short_dirs, i_basename);
	free(short_dirs);
}
