/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:45:58 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 21:45:59 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include <unistd.h>

static void	init_game_state(t_app *app)
{
	app->game->player_x = app->map->player_x;
	app->game->player_y = app->map->player_y;
	app->game->moves = 0;
	app->game->collected = 0;
	app->game->finished = 0;
}

static int	init_window(t_app *app)
{
	int	width;
	int	height;

	width = app->map->cols * TILE_SIZE;
	height = app->map->rows * TILE_SIZE;
	app->window->width = width;
	app->window->height = height;
	app->window->name = WIN_NAME;
	app->window->win_ptr = mlx_new_window(app->mlx_ptr, width, height,
			(char *)WIN_NAME);
	if (!app->window->win_ptr)
	{
		ft_fprintf(STDERR_FILENO, "Error\nmlx_new_window() failed!\n");
		return (0);
	}
	return (1);
}

int	init_app(t_app *app)
{
	app->mlx_ptr = mlx_init();
	if (!app->mlx_ptr)
	{
		ft_fprintf(STDERR_FILENO, "Error\nmlx_init() failed!\n");
		return (0);
	}
	if (!init_window(app))
		return (0);
	init_game_state(app);
	return (1);
}
