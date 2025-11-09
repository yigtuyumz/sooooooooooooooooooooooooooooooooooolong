/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:46:50 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 21:46:51 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include <fcntl.h>
#include <unistd.h>

static void	strip_newlines(t_map *map)
{
	int	i;
	int	len;

	i = 0;
	while (i < map->rows)
	{
		len = utils_strlen(map->grid[i]);
		if (len > 0 && map->grid[i][len - 1] == '\n')
			map->grid[i][len - 1] = '\0';
		i++;
	}
}

int	map_read(t_map *map, const char *path)
{
	t_map_node	*list;
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	list = read_to_list(fd, &map->rows);
	close(fd);
	if (!list)
		return (0);
	map->grid = list_to_array(list, map->rows);
	free_list(list);
	if (!map->grid)
		return (0);
	strip_newlines(map);
	if (map->rows > 0)
		map->cols = utils_strlen(map->grid[0]);
	else
		map->cols = 0;
	return (1);
}
