/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:45:53 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 21:45:54 by yuyumaz          ###   ########.fr       */
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

void	free_game(t_app **app)
{
	if (!app || !*app || !(*app)->game)
		return ;
	(*app)->game->moves = 0;
	(*app)->game->collected = 0;
	(*app)->game->player_x = 0;
	(*app)->game->player_y = 0;
	(*app)->game->finished = 0;
	free((void *)(*app)->game);
	(*app)->game = NULL;
}

void	*free_app(t_app **app)
{
	if (!app || !*app)
		return (NULL);
	free_game(app);
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
