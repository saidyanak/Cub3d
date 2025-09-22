/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syanak <syanak@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:02:22 by syanak            #+#    #+#             */
/*   Updated: 2025/09/22 18:02:18 by syanak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUD3D_H
# define CUD3D_H

# include "get_next_line/get_next_line.h"
# include <stddef.h>

typedef struct s_map_info
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		**map;
	int			ceiling_c;
	int			floor_c;

}				t_map_info;

typedef struct s_base
{
	t_map_info	*map_info;
}				t_base;

size_t			ft_strlen(const char *str);
int				map_control(int ac, char **av);
char			**copy_map(char *av);

// get_next_line
size_t			ft_len(t_list *list);
t_list			*ft_last_node(t_list *list);
int				ft_found_nl(t_list *list);
void			copy_line(t_list *list, char *line);
void			ft_free_linked_list(t_list **list, t_list *new_node, char *buf);
char			*get_next_line(int fd);

#endif