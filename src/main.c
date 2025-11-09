/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 08:22:37 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 20:18:59 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "solong.h"

int	main(int argc, char *argv[])
{
	t_app	*app;

	if (argc != 2)
	{
		(void) ft_fprintf(STDERR_FILENO,
			"Error\nUsage: %s <map.ber>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (!map_check_extension(argv[1]))
	{
		(void) ft_fprintf(STDERR_FILENO,
			"Error\nMap file must have .ber extension\n");
		exit(EXIT_FAILURE);
	}
	if (!map_check_file_exists(argv[1]))
	{
		(void) ft_fprintf(STDERR_FILENO,
			"Error\nCannot open map file: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	app = alloc_app();
	if (!app)
		exit(EXIT_FAILURE);
	if (!map_read(app->map, argv[1]))
	{
		(void) ft_fprintf(STDERR_FILENO, "Error\nFailed to read map!\n");
		free_app(&app);
		exit(EXIT_FAILURE);
	}
	if (!map_validate(app->map))
	{
		free_app(&app);
		exit(EXIT_FAILURE);
	}
	app->mlx_ptr = mlx_init();
	if (!app->mlx_ptr)
	{
		(void) ft_fprintf(STDERR_FILENO, "Error\nmlx_init() failed!\n");
		(void) free_app(&app);
		exit(EXIT_FAILURE);
	}
	app->window->win_ptr = mlx_new_window(app->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (!app->window->win_ptr)
	{
		(void) ft_fprintf(STDERR_FILENO, "Error\nmlx_new_window() failed!\n");
		(void) free_app(&app);
		exit(EXIT_FAILURE);
	}
	sleep(1);
	free_app(&app);
	return (0);
}
