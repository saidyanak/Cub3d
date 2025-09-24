/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syanak <syanak@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:28:51 by syanak            #+#    #+#             */
/*   Updated: 2025/09/24 17:23:48 by syanak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Hata durumunda tüm ayrılmış hafızayı güvenli bir şekilde temizler.
void	free_map_info(t_map_info *info)
{
	int	i;

	if (!info)
		return ;
	if (info->north)
		free(info->north);
	if (info->south)
		free(info->south);
	if (info->west)
		free(info->west);
	if (info->east)
		free(info->east);
	if (info->map)
	{
		i = 0;
		while (info->map[i])
		{
			free(info->map[i]);
			i++;
		}
		free(info->map);
	}
	free(info);
}

// Okunan satırın tipini belirleyip ilgili yardımcıyı çağıran fonksiyon
static int	handle_line(char *line, t_map_info *info)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (parse_texture(line + i + 2, &info->north));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (parse_texture(line + i + 2, &info->south));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (parse_texture(line + i + 2, &info->west));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (parse_texture(line + i + 2, &info->east));
	else if (line[i] == 'F')
		return (parse_color(line + i + 1, &info->floor_c));
	else if (line[i] == 'C')
		return (parse_color(line + i + 1, &info->ceiling_c));
	else if (line[i] == '1' || line[i] == ' ')
		return (2);
	else if (line[i] == '\0')
		return (1);
	return (0);
}

static int	validate_all_elements_found(t_map_info *info)
{
	if (!info->north || !info->south || !info->west || !info->east
		|| info->floor_c == -1 || info->ceiling_c == -1 || !info->map)
	{
		printf("Error\nMissing element in scene file\n");
		return (0);
	}
	// if (!is_map_closed(info->map))
	//    return (0);
	return (1);
}

void	init_map_info(t_map_info *s_map_info)
{
	s_map_info->ceiling_c = -1;
	s_map_info->east = NULL;
	s_map_info->floor_c = -1;
	s_map_info->map = NULL;
	s_map_info->map_height = -1;
	s_map_info->map_width = -1;
	s_map_info->north = NULL;
	s_map_info->south = NULL;
	s_map_info->west = NULL;
}

int	import_map(t_base *base, char *filepath)
{
	int		fd;
	char	*line;
	int		status;

	base->map_info = malloc(sizeof(t_map_info));
	if (!base->map_info)
		return (0);
	init_map_info(base->map_info); // Tüm değerleri NULL/-1 yap
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nOpen error"), free_map_info(base->map_info), 0);
	line = get_next_line(fd);
	while (line)
	{
		status = handle_line(line, base->map_info);// texture ları ve color u alma işlemini iyice detaylı bakmak lazım
		if (status == 0) // Hata
			return (printf("Error\nParse Error"), free(line),
				free_map_info(base->map_info), close(fd), 0);
		if (status == 2) // Harita başladı
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (line) // Harita okumaya başla
		read_map_grid(fd, line, base->map_info);
	close(fd);
	if (!validate_all_elements_found(base->map_info))
		return (free_map_info(base->map_info), 0);
	// burda birde player 1 tane mi diye de kontrol etmeliyiz burası onemli bi tık map de var burda
	return (1);
}
