/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auto <auto@local>                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 00:00:00 by auto              #+#    #+#             */
/*   Updated: 2025/09/26 00:00:00 by auto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>

// is_valid_char: harita karakterinin geçerli olup olmadığını kontrol eder
static int is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

// count_players: haritada kaç oyuncu olduğunu sayar
int count_players(char **map)
{
    int i = 0;
    int j;
    int count = 0;
    if (!map)
        return 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
                count++;
            j++;
        }
        i++;
    }
    return count;
}

// flood_fill: harita kopyasında dışarıdan erişilebilen hücreleri 'X' ile işaretler
static void flood_fill(char **copy, int rows, int cols)
{
    int max = rows * cols;
    int *stack = malloc(sizeof(int) * max);
    int top = 0;
    int r = 0, c = 0, idx = 0;
    if (!stack)
        return;
    r = 0;
    while (r < rows)
    {
        c = 0;
        while (c < cols)
        {
            if (r == 0 || c == 0 || r == rows - 1 || c == cols - 1)
            {
                char ch = copy[r][c];
                if (ch != '1' && ch != 'X')
                {
                    stack[top++] = r * cols + c;
                }
            }
            c++;
        }
        r++;
    }
    while (top > 0)
    {
        idx = stack[--top];
        r = idx / cols; c = idx % cols;
        if (r < 0 || c < 0 || r >= rows || c >= cols)
            continue;
        if (copy[r][c] == '1' || copy[r][c] == 'X')
            continue;
        copy[r][c] = 'X';
        if (r - 1 >= 0) stack[top++] = (r - 1) * cols + c;
        if (r + 1 < rows) stack[top++] = (r + 1) * cols + c;
        if (c - 1 >= 0) stack[top++] = r * cols + (c - 1);
        if (c + 1 < cols) stack[top++] = r * cols + (c + 1);
        if (top >= max) break;
    }
    free(stack);
}

// is_map_closed: haritanın dışarıdan erişilemez olup olmadığını kontrol eder
int is_map_closed(char **map)
{
    int rows = 0;
    int cols = 0;
    int i = 0, j = 0;
    char **copy;
    if (!map)
        return 0;
    while (map[rows])
    {
        int len = 0;
        while (map[rows][len])
            len++;
        if (len > cols) cols = len;
        rows++;
    }
    if (rows == 0)
        return 0;
    copy = malloc(sizeof(char *) * (rows + 1));
    if (!copy)
        return 0;
    i = 0;
    while (i < rows)
    {
        copy[i] = malloc(cols + 1);
        if (!copy[i])
        {
            while (i-- > 0) free(copy[i]);
            free(copy);
            return 0;
        }
        j = 0;
        while (j < cols)
        {
            if (j < (int)ft_strlen(map[i]))
                copy[i][j] = map[i][j];
            else
                copy[i][j] = ' ';
            j++;
        }
        copy[i][cols] = '\0';
        i++;
    }
    copy[rows] = NULL;
    flood_fill(copy, rows, cols);
    i = 0;
    while (i < rows)
    {
        j = 0;
        while (j < cols)
        {
            if (copy[i][j] == 'X')
            {
                if (j < (int)ft_strlen(map[i]))
                {
                    char orig = map[i][j];
                    if (orig == '0' || orig == 'N' || orig == 'S' || orig == 'E' || orig == 'W')
                    {
                        int k = 0;
                        while (k < rows)
                        {
                            free(copy[k]);
                            k++;
                        }
                        free(copy);
                        return 0;
                    }
                }
            }
            j++;
        }
        i++;
    }
    i = 0;
    while (i < rows)
    {
        free(copy[i]);
        i++;
    }
    free(copy);
    return 1;
}

// validate_map: harita ve parametrelerin doğruluğunu kontrol eder
int validate_map(t_map_info *info)
{
    int i = 0, j = 0;
    if (!info || !info->map)
        return 0;
    info->map_width = 0;
    while (info->map[i])
    {
        j = 0;
        while (info->map[i][j])
        {
            if (!is_valid_char(info->map[i][j]))
            {
                printf("Error\nInvalid character '%c' in map.\n", info->map[i][j]);
                return 0;
            }
            j++;
        }
        if (j > info->map_width) info->map_width = j;
        i++;
    }
    info->map_height = i;
    if (count_players(info->map) != 1)
    {
        printf("Error\nMap must contain exactly one player start (N/S/E/W).\n");
        return 0;
    }
    if (!is_map_closed(info->map))
    {
        printf("Error\nMap is not closed/surrounded by walls.\n");
        return 0;
    }
    if (player_on_edge(info->map))
    {
        printf("Error\nPlayer start position must not be on the map edge.\n");
        return 0;
    }
    return 1;
}

// player_on_edge: oyuncu harita kenarında mı kontrol eder
int player_on_edge(char **map)
{
    int i = 0;
    int j = 0;
    if (!map)
        return 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
            {
                if (i == 0 || map[i + 1] == NULL || j == 0 || j == (int)ft_strlen(map[i]) - 1)
                    return 1;
            }
            j++;
        }
        i++;
    }
    return 0;
}