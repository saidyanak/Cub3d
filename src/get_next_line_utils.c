/* Minimal utils for get_next_line (stubs) */
#include <stdlib.h>

size_t	g_strlen(const char *s)
{
    size_t i = 0;
    if (!s) return 0;
    while (s[i]) i++;
    return i;
}

char	*g_strdup(const char *s)
{
    size_t n = g_strlen(s);
    char *r = malloc(n + 1);
    if (!r) return NULL;
    for (size_t i = 0; i < n; ++i) r[i] = s[i];
    r[n] = '\0';
    return r;
}
