/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:45:36 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 21:58:53 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "solong.h"

void	*alloc_window(t_app **app)
{
	if (!app || !*app)
		return (NULL);
	(*app)->window = (t_window *) malloc(sizeof(t_window));
	if (!(*app)->window)
	{
		ft_fprintf(STDERR_FILENO, "malloc for t_window *window failed!\n");
		return (NULL);
	}
	(*app)->window->width = 0;
	(*app)->window->height = 0;
	(*app)->window->tile_width = 0;
	(*app)->window->tile_height = 0;
	(*app)->window->name = NULL;
	(*app)->window->win_ptr = NULL;
	return (*app);
}

void	*alloc_map(t_app **app)
{
	if (!app || !*app)
		return (NULL);
	(*app)->map = (t_map *) malloc(sizeof(t_map));
	if (!(*app)->map)
	{
		ft_fprintf(STDERR_FILENO, "malloc for t_app *app failed!\n");
		return (NULL);
	}
	(*app)->map->fd = -1;
	(*app)->map->path = NULL;
	(*app)->map->grid = NULL;
	(*app)->map->rows = -1;
	(*app)->map->cols = -1;
	(*app)->map->player_x = -1;
	(*app)->map->player_y = -1;
	(*app)->map->exit_x = -1;
	(*app)->map->exit_y = -1;
	(*app)->map->collectibles = -1;
	return (*app);
}

void	*alloc_game(t_app **app)
{
	if (!app || !*app)
		return (NULL);
	(*app)->game = (t_game *)malloc(sizeof(t_game));
	if (!(*app)->game)
	{
		ft_fprintf(STDERR_FILENO, "malloc for t_game failed!\n");
		return (NULL);
	}
	(*app)->game->moves = 0;
	(*app)->game->collected = 0;
	(*app)->game->player_x = 0;
	(*app)->game->player_y = 0;
	(*app)->game->finished = 0;
	return (*app);
}

t_app	*alloc_app(void)
{
	t_app	*app;

	app = (t_app *) malloc(sizeof(t_app));
	if (!app)
	{
		ft_fprintf(STDERR_FILENO, "malloc for t_app *app failed!\n");
		return (NULL);
	}
	app->map = NULL;
	app->mlx_ptr = NULL;
	app->window = NULL;
	app->game = NULL;
	if (!alloc_window(&app))
		return (free_app(&app));
	if (!alloc_map(&app))
		return (free_app(&app));
	if (!alloc_game(&app))
		return (free_app(&app));
	return (app);
}
