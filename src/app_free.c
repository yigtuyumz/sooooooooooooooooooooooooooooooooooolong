/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:32:51 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 20:38:06 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	free_window(t_app **app)
{
	if (!app || !*app || !(*app)->window)
		return ;
	if ((*app)->mlx_ptr && (*app)->window->win_ptr)
		(void) mlx_destroy_window((*app)->mlx_ptr, (*app)->window->win_ptr);
	(*app)->window->win_ptr = NULL;
	(*app)->window->width = 0;
	(*app)->window->height = 0;
	(*app)->window->name = NULL;
	free((void *)(*app)->window);
	(*app)->window = NULL;
}

void	free_map(t_app **app)
{
	int	i;

	if (!app || !*app || !(*app)->map)
		return ;
	if ((*app)->map->grid)
	{
		i = 0;
		while ((*app)->map->grid[i])
		{
			free((void *)(*app)->map->grid[i]);
			(*app)->map->grid[i] = NULL;
			i++;
		}
		free((*app)->map->grid);
		(*app)->map->grid = NULL;
	}
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

void	*free_app(t_app **app)
{
	if (!app || !*app)
		return (NULL);
	free_map(app);
	free_window(app);
	if ((*app)->mlx_ptr)
	{
		(void) mlx_destroy_display((*app)->mlx_ptr);
		free((void *)(*app)->mlx_ptr);
		(*app)->mlx_ptr = NULL;
	}
	free((void *) *app);
	*app = NULL;
	return (NULL);
}
