/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:46:24 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 21:46:24 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	check_position(t_map *map, int i, int j, int *counts)
{
	if (map->grid[i][j] == 'P')
	{
		counts[0]++;
		map->player_x = j;
		map->player_y = i;
	}
	else if (map->grid[i][j] == 'E')
	{
		counts[1]++;
		map->exit_x = j;
		map->exit_y = i;
	}
	else if (map->grid[i][j] == 'C')
		map->collectibles++;
	else if (map->grid[i][j] != '0' && map->grid[i][j] != '1'
		&& map->grid[i][j] != '\n')
		counts[2] = 1;
}

int	check_elements(t_map *map)
{
	int	i;
	int	j;
	int	counts[3];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	map->collectibles = 0;
	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
			check_position(map, i, j, counts);
	}
	if (counts[2])
		return (0);
	return (counts[0] == 1 && counts[1] == 1 && map->collectibles > 0);
}
