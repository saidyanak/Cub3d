/* Minimal, blocking get_next_line implementation for testing purposes. */
#include "get_next_line.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char	*str_join(char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	if (s1 == NULL)
		len1 = 0;
	else
		len1 = strlen(s1);
	if (s2 == NULL)
		len2 = 0;
	else
		len2 = strlen(s2);
	new_str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new_str)
	{
		free(s1);
		return (NULL);
	}
	if (s1)
		memcpy(new_str, s1, len1);
	if (s2)
		memcpy(new_str + len1, s2, len2);
	new_str[len1 + len2] = '\0';
	free(s1);
	return (new_str);
}

char	*get_next_line(int fd)
{
	char	buf[2];
	char	*line;
	ssize_t	r;

	if (fd < 0)
		return (NULL);
	line = NULL;
	while ((r = read(fd, buf, 1)) > 0)
	{
		buf[r] = '\0';
		line = str_join(line, buf);
		if (line && line[strlen(line) - 1] == '\n')
			break ;
	}
	if (!line)
		return (NULL);
	if (r == 0 && strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
/* Minimal, blocking get_next_line implementation for testing purposes. */
