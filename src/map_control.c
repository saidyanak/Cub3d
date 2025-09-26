/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syanak <syanak@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:30:13 by syanak            #+#    #+#             */
/*   Updated: 2025/09/22 17:57:08 by syanak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <stdio.h>

int	namespace_control(char **av)
{
	int	i;

	i = 0;
	while (av[1][i])
		i++;
	i -= 4;
	if (!(av[1][i] == '.') && !(av[1][i + 1] == 'c') && !(av[1][i + 2] == 'u')
		&& !(av[1][i + 3] == 'b'))
		return (0);
	if (open(av[1], O_RDONLY) < 0)
		return (0);
	return (1);
}

int	map_control(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\nToo many arguments. Usage: ./cub3d <path_to_map.cub>\n");
		return (0);
	}
	else if (!(namespace_control(av)))
	{
		printf("Error\nMap Name Space error\n");
		return (0);
	}
	return (1);
}