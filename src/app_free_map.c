/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_free_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:45:43 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 21:45:49 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free((void *)grid[i]);
		grid[i] = NULL;
		i++;
	}
	free((void *) grid);
}

void	free_map(t_app **app)
{
	if (!app || !*app || !(*app)->map)
		return ;
	free_grid((*app)->map->grid);
	(*app)->map->grid = NULL;
	(*app)->map->fd = -1;
	(*app)->map->path = NULL;
	(*app)->map->rows = -1;
	(*app)->map->cols = -1;
	(*app)->map->player_x = -1;
	(*app)->map->player_y = -1;
	(*app)->map->exit_x = -1;
	(*app)->map->exit_y = -1;
	(*app)->map->collectibles = -1;
	free((void *)(*app)->map);
	(*app)->map = NULL;
}
