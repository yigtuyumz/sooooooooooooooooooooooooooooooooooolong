/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 22:00:00 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 22:00:47 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	draw_tile(t_app *app, int x, int y, int color)
{
	int	i;
	int	j;
	int	px;
	int	py;

	i = 0;
	while (i < app->window->tile_height)
	{
		j = 0;
		while (j < app->window->tile_width)
		{
			px = x * app->window->tile_width + j;
			py = y * app->window->tile_height + i;
			mlx_pixel_put(app->mlx_ptr, app->window->win_ptr, px, py, color);
			j++;
		}
		i++;
	}
}

static int	get_tile_color(char c)
{
	if (c == '1')
		return (0x808080);
	else if (c == 'P')
		return (0x00FF00);
	else if (c == 'E')
		return (0xFF0000);
	else if (c == 'C')
		return (0xFFFF00);
	else
		return (0x0000FF);
}

void	render_map(t_app *app)
{
	int	y;
	int	x;

	y = 0;
	while (y < app->map->rows)
	{
		x = 0;
		while (x < app->map->cols)
		{
			draw_tile(app, x, y, get_tile_color(app->map->grid[y][x]));
			x++;
		}
		y++;
	}
}
