/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syanak <syanak@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:05:09 by syanak            #+#    #+#             */
/*   Updated: 2025/09/22 18:10:11 by syanak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	base_init(t_base *base)
{
	base->map_info = NULL;
}

int	import_map(t_base *base, char *av)
{
	
}

int	main(int ac, char **av)
{
	t_base base;

	base_init(&base);
	if (!(map_control(ac, av)) || !(import_map(&base, av[1])))
		return (1);
	return (0);
}