/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syanak <syanak@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:02:22 by syanak            #+#    #+#             */
/*   Updated: 2025/09/24 17:00:21 by syanak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h> // Hata mesajları için (isteğe bağlı)
# include <stdlib.h>
# include <unistd.h>

// Libft fonksiyonlarının prototiplerini içeren header
// # include "libft/libft.h"

// Struct'ların aynı
typedef struct s_map_info
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		**map;
	int			ceiling_c;
	int			floor_c;
	int			map_width;
	int			map_height;
}				t_map_info;

typedef struct s_base
{
	t_map_info	*map_info;
}				t_base;

// --- PARSING FONKSİYONLARI ---
int				import_map(t_base *base, char *filepath);
void			free_map_info(t_map_info *map_info);
// --- libft'de olması beklenen fonksiyonlar (eğer yoksa) ---
char			**ft_split(char const *s, char c);
t_list			*ft_lstnew(void *content);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstadd_back(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
char			*ft_strdup(const char *s1);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *str);
int				ft_isspace(char c);
// ...ve diğer libft fonksiyonları

// --- GENEL YARDIMCILAR ---
int				map_control(int ac, char **av);
int				read_map_grid(int fd, char *first_line, t_map_info *map_info);
int				parse_color(char *line, int *dest);
int				parse_texture(char *line, char **dest);

#endif