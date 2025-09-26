/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syanak <syanak@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:04:04 by syanak            #+#    #+#             */
/*   Updated: 2025/09/24 17:04:22 by syanak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

// ft_split'in ayırdığı hafızayı temizleyen yardımcı fonksiyon.
static void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	if (tokens)
		free(tokens);
}

// Bir string'in sadece sayısal karakterlerden oluşup oluşmadığını kontrol eder.
static int	is_str_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// GNL'den gelen satırın sonundaki '\n' karakterini siler.
static void	trim_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

// "NO   ./path/to/file.xpm" gibi bir satırı ayrıştırır
int	parse_texture(char *line, char **dest)
{
	int	i;

	if (*dest != NULL)
		return (printf("Error\nDuplicate texture identifier found.\n"), 0);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0')
		return (printf("Error\nTexture path is missing.\n"), 0);
	trim_newline(line + i);
	*dest = ft_strdup(line + i);
	if (!*dest)
		return (printf("Error\nMalloc failed while parsing texture.\n"), 0);
	/* Check that texture file exists and is readable */
	{
		int fd = open(*dest, O_RDONLY);
		if (fd < 0)
		{
			printf("Error\nTexture file not found or not readable: %s\n", *dest);
			free(*dest);
			*dest = NULL;
			return (0);
		}
		close(fd);
	}
	return (1);
}

// "F 220,100,0" gibi bir satırı ayrıştırır
int	parse_color(char *line, int *dest)
{
	char	**rgb_values;
	int		colors[3];
	int		i;
	int		count;

	if (*dest != -1)
		return (printf("Error\nDuplicate color identifier found.\n"), 0);
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	rgb_values = ft_split(line, ',');
	if (!rgb_values)
		return (printf("Error\nMalloc failed during color parsing.\n"), 0);
	count = 0;
	while (rgb_values[count])
		count++;
	if (count != 3)
	{
		free_tokens(rgb_values);
		return (printf("Error\nColor must have 3 values (R,G,B).\n"), 0);
	}
	i = -1;
	while (++i < 3)
	{
		trim_newline(rgb_values[i]); // Her ihtimale karşı...
		if (!is_str_numeric(rgb_values[i]))
		{
			free_tokens(rgb_values);
			return (printf("Error\nColor value contains non-numeric characters.\n"),
				0);
		}
		colors[i] = ft_atoi(rgb_values[i]);
		if (colors[i] < 0 || colors[i] > 255)
		{
			free_tokens(rgb_values);
			return (printf("Error\nColor value out of range [0-255].\n"), 0);
		}
	}
	*dest = (colors[0] << 16) | (colors[1] << 8) | colors[2];
	free_tokens(rgb_values);
	return (1);
}

// Harita verisini bir linked list kullanarak okur ve char** dizisine dönüştürür.
int	read_map_grid(int fd, char *first_line, t_map_info *map_info)
{
	t_list	*head;
	t_list	*current;
	char	*line;
	int		i;

	head = NULL;
	trim_newline(first_line);
	ft_lstadd_back(&head, ft_lstnew(first_line));
	if (!head)
		return (free(first_line), 0);
	line = get_next_line(fd);
	while (line)
	{
		trim_newline(line);
		if (ft_strlen(line) == 0 && ft_lstsize(head) > 0)
		{
			free(line);
			ft_lstclear(&head, free);
			return (printf("Error\nEmpty line inside or after map definition.\n"),
				0);
		}
		ft_lstadd_back(&head, ft_lstnew(line));
		line = get_next_line(fd);
	}
	map_info->map_height = ft_lstsize(head);
	map_info->map = malloc(sizeof(char *) * (map_info->map_height + 1));
	if (!map_info->map)
		return (ft_lstclear(&head, free), 0);
	current = head;
	i = 0;
	while (current)
	{
		map_info->map[i] = (char *)current->content;
		current->content = NULL;
		i++;
		current = current->next;
	}
	map_info->map[i] = NULL;
	ft_lstclear(&head, free);
	return (1);
}
