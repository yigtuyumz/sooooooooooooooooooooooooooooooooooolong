/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_shape.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:46:31 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 21:46:32 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include <unistd.h>

int	check_rectangular(t_map *map)
{
	int	i;
	int	len;

	if (!map || !map->grid || map->rows == 0)
		return (0);
	i = 0;
	while (i < map->rows)
	{
		len = utils_strlen(map->grid[i]);
		if (len == 0)
		{
			ft_fprintf(STDERR_FILENO, "Error\nEmpty line in map\n");
			return (0);
		}
		if (len != map->cols)
		{
			ft_fprintf(STDERR_FILENO, "Error\nMap is not rectangular\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_walls(t_map *map)
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
