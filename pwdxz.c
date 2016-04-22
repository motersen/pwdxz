#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	if (argc < 2) {
		fprintf(stderr, "Error: No directory specified\n");
		return 1;
	}
	char *home = getenv("HOME");
	size_t l_home = strlen(home);
	char *cwd = argv[1];
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
	char *short_dirs = malloc(sizeof(char) * (2 * (depth - 1) + 1));
	for (char *i = i_midpath, *j = short_dirs; i < i_basename; i++)
		if (*i == '/') {
			*(j++) = '/';
			*(j++) = *(++i);
		}
	*(short_dirs + 2 * (depth - 1)) = '\0';
	// print prefix
	if (sub_home)
		printf("~");
	printf("%s%s\n", short_dirs, i_basename);
	free(short_dirs);
}
