/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:00:00 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 17:55:15 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include <unistd.h>

static int	check_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->cols)
	{
		if (map->grid[0][i] != '1' || map->grid[map->rows - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < map->rows)
	{
		if (map->grid[i][0] != '1' || map->grid[i][map->cols - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	check_elements(t_map *map)
{
	int	i;
	int	j;
	int	player_count;
	int	exit_count;

	player_count = 0;
	exit_count = 0;
	map->collectibles = 0;
	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			if (map->grid[i][j] == 'P' && ++player_count)
			{
				map->player_x = j;
				map->player_y = i;
			}
			else if (map->grid[i][j] == 'E' && ++exit_count)
			{
				map->exit_x = j;
				map->exit_y = i;
			}
			else if (map->grid[i][j] == 'C')
				map->collectibles++;
			else if (map->grid[i][j] != '0' && map->grid[i][j] != '1'
				&& map->grid[i][j] != '\n')
				return (0);
		}
	}
	return (player_count == 1 && exit_count == 1 && map->collectibles > 0);
}

static void	floodfill(char **grid, int x, int y, int *visited)
{
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return ;
	if (grid[y][x] == 'E')
		(*visited) |= 1;
	if (grid[y][x] == 'C')
		(*visited) |= 2;
	grid[y][x] = 'V';
	floodfill(grid, x + 1, y, visited);
	floodfill(grid, x - 1, y, visited);
	floodfill(grid, x, y + 1, visited);
	floodfill(grid, x, y - 1, visited);
}

static char	**copy_grid(t_map *map)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (map->rows + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->rows)
	{
		copy[i] = utils_strdup(map->grid[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	check_path(t_map *map)
{
	char	**grid_copy;
	int		visited;
	int		i;
	int		collectibles_found;

	grid_copy = copy_grid(map);
	if (!grid_copy)
		return (0);
	visited = 0;
	floodfill(grid_copy, map->player_x, map->player_y, &visited);
	collectibles_found = 0;
	i = -1;
	while (++i < map->rows)
	{
		int j = -1;
		while (++j < map->cols)
		{
			if (grid_copy[i][j] == 'C')
				collectibles_found++;
		}
	}
	i = -1;
	while (++i < map->rows)
		free(grid_copy[i]);
	free(grid_copy);
	return ((visited & 1) && collectibles_found == 0);
}

int	map_validate(t_map *map)
{
	if (!map || !map->grid || map->rows < 3 || map->cols < 3)
	{
		ft_fprintf(STDERR_FILENO, "Error\nInvalid map dimensions\n");
		return (0);
	}
	if (!check_walls(map))
	{
		ft_fprintf(STDERR_FILENO, "Error\nMap not surrounded by walls\n");
		return (0);
	}
	if (!check_elements(map))
	{
		ft_fprintf(STDERR_FILENO, "Error\nInvalid map elements\n");
		return (0);
	}
	if (!check_path(map))
	{
		ft_fprintf(STDERR_FILENO, "Error\nNo valid path to exit/collectibles\n");
		return (0);
	}
	return (1);
}
