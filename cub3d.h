/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syanak <syanak@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:02:22 by syanak            #+#    #+#             */
/*   Updated: 2025/09/16 17:05:47 by syanak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUD3D_H
# define CUD3D_H

# include <stddef.h>

typedef struct s_base
{
}		t_base;

size_t	ft_strlen(char *str);
int		map_control(int ac, char **av);

#endif