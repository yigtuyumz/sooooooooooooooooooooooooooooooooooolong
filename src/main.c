/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 08:22:37 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/08 09:32:15 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "solong.h"

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	t_app	*app;

	app = alloc_app();
	if (!app)
		exit(EXIT_FAILURE);
	app->mlx_ptr = mlx_init();
	if (!app->mlx_ptr)
	{
		ft_fprintf(STDERR_FILENO, "mlx_init() failed!\n");
		(void) free_app(&app);
		exit(EXIT_FAILURE);
	}
	app->window->win_ptr = mlx_new_window(app->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (!app->window->win_ptr)
	{
		ft_fprintf(STDERR_FILENO, "mlx_new_window() failed!\n");
		(void) free_app(&app);
		exit(EXIT_FAILURE);
	}
	sleep(1);
	free_app(&app);
	return (0);
}
