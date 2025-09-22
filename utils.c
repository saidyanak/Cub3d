/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syanak <syanak@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:04:04 by syanak            #+#    #+#             */
/*   Updated: 2025/09/22 16:16:51 by syanak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

void	check_double_nl(char *line, int fd)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n' && (line[i + 1] == '\n' || line[1] == '\0'))
		{
			write(1, "Error\nMap", 10);
			free(line);
			close(fd);
			exit(1);
		}
		i++;
	}
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

#include <stddef.h>
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	index;

	ptr = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!ptr)
		return (NULL);
	index = 0;
	while (s1[index])
	{
		ptr[index] = s1[index];
		index++;
	}
	ptr[index] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (s1len + s2len + 1));
	if (!ret)
		return (NULL);
	while (*s1)
		*ret++ = *s1++;
	while (*s2)
		*ret++ = *s2++;
	*ret = 0;
	return (ret - (s1len + s2len));
}

#include <stdlib.h>

static char	**free_mem(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static int	count_words(const char *str, char sep)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == sep)
			str++;
		else
		{
			count++;
			while (*str != '\0' && *str != sep)
				str++;
		}
	}
	return (count);
}

static int	word_len(const char *str, char sep)
{
	int	len;

	len = 0;
	while (*str != '\0' && *str != sep)
	{
		len++;
		str++;
	}
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize)
	{
		while (i < dstsize - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (ft_strlen(src));
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	arr = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0' && *s != c)
		{
			arr[i] = (char *)malloc((word_len(s, c) + 1) * sizeof(char));
			if (arr[i] == NULL)
				return (free_mem(arr));
			ft_strlcpy(arr[i], s, (word_len(s, c) + 1));
			s += word_len(s, c);
			i++;
		}
	}
	arr[i] = NULL;
	return (arr);
}

char	**copy_map(char *av)
{
	char **map;
	char *holder_map;
	char *holder;
	char *line;
	int fd;

	holder = NULL;
	line = NULL;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (NULL);
	holder_map = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		holder = holder_map;
		holder_map = ft_strjoin(holder, line);
		free(line);
		free(holder);
	}
	check_double_nl(holder_map, fd);
	map = ft_split(holder_map, '\n');
	return (free(holder_map), close(fd), map);
}
