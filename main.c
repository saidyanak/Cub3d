/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syanak <syanak@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:05:09 by syanak            #+#    #+#             */
/*   Updated: 2025/09/24 17:21:38 by syanak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	base_init(t_base *base)
{
	base->map_info = NULL;
}

int	main(int ac, char **av)
{
	t_base base;

	base_init(&base);
	if (!map_control(ac, av) || !import_map(&base, av[1]))
		return (1);
	// Eğer buraya geldiyse,
	// base.map_info içinde her şey hazır demektir. Şimdi map in içerisindeki verileri karşılaştırmak lazım Oyuncu erişilebilirilk vsvs
	// Ardından oyun motorunu başlatabilirsin.

	// Oyun bittiğinde tüm hafızayı temizle
	free_map_info(base.map_info);
	return (0);
}