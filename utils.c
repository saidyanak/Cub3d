/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syanak <syanak@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:04:04 by syanak            #+#    #+#             */
/*   Updated: 2025/09/16 17:57:51 by syanak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str++)
		i++;
	return (i);
}

char	**copy_map(char *av)
{
	char	**map;
	int		fd;
	int		i;

	i = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (close(fd), NULL);
	map = NULL;
	map[i] = malloc(sizeof(char *));
	if (!map[i])
		return (NULL);
	map[i] = get_next_line(fd);
	if (!map[i])
		return (NULL);
	while (map)
	{
		i++;
		map[i] = get_next_line(fd);
		if (!map[i])
			return (NULL);
	}
	map[i] = NULL;
	return (map);
}
