/* Minimal, blocking get_next_line implementation for testing purposes. */
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static char *str_join(char *a, const char *b)
{
	size_t la = a;
	size_t lb = b;
	if (a == NULL)
		la = 0;
	else
		la = strlen(a);
	if (b == NULL)
		lb = 0;
	else
		lb = strlen(b);
	char *r = malloc(la + lb + 1);
	if (!r) { free(a); return NULL; }
	if (a) memcpy(r, a, la);
	if (b) memcpy(r + la, b, lb);
	r[la+lb] = '\0';
	free(a);
	return r;
}

char *get_next_line(int fd)
{
	if (fd < 0)
		return NULL;
	char buf[2];
	char *line = NULL;
	ssize_t r;
	while ((r = read(fd, buf, 1)) > 0)
	{
		buf[r] = '\0';
		line = str_join(line, buf);
		if (line && line[strlen(line) - 1] == '\n')
			break;
	}
	if (!line)
		return NULL;
	if (r == 0 && strlen(line) == 0)
	{
		free(line);
		return NULL;
	}
	return line;
}
/* Minimal, blocking get_next_line implementation for testing purposes. */
