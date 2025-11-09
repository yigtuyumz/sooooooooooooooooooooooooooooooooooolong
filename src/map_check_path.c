/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:46:27 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 21:46:28 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

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
				free((void *) copy[i]);
			free((void *) copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	count_unreachable(char **grid, t_map *map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (grid[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static void	free_grid_copy(char **grid, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free((void *) grid[i]);
		i++;
	}
	free((void *) grid);
}

int	check_path(t_map *map)
{
	char	**grid_copy;
	int		visited;
	int		collectibles_found;

	grid_copy = copy_grid(map);
	if (!grid_copy)
		return (0);
	visited = 0;
	floodfill(grid_copy, map->player_x, map->player_y, &visited);
	collectibles_found = count_unreachable(grid_copy, map);
	free_grid_copy(grid_copy, map->rows);
	return ((visited & 1) && collectibles_found == 0);
}
