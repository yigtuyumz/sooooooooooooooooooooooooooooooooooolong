/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 08:22:37 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/01 23:09:15 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"
#include "logger.h"
#include "utils.h"

// destroy sirasi
// image, window, display

// man kurulumu
// manpath
//
// Sistem genelinde kurulum:
// sudo cp -r minilibx-linux/man/man1 /usr/local/share/man
// sudo cp -r minilibx-linux/man/man3 /usr/local/share/man
//
// man database guncelleme
// mandb

// git submodule eklemek icin
// git submodule add https://github.com/42paris/minilibx-linux

// submodule'ler ile birlikte git clone
// git clone --recurse-submodules <repo-url>

// TODO line 68: maybe garbage collecting in the future??
int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_logger	*logger;

	logger = logger_init("out.log", "err.log", "info.log", "warn.log");
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
	{
		utils_putstr(STDERR_FILENO, "mlx init failed!\n");
		return (1);
	}
	utils_putstr(STDOUT_FILENO, "mlx initialized!\n");
	win_ptr = mlx_new_window(mlx_ptr, 300, 300, "Hello, World!");
	if (!win_ptr)
	{
		utils_putstr(STDERR_FILENO, "Window create failed!\n");
		if (mlx_ptr)
		{
			mlx_destroy_display(mlx_ptr);
			free(mlx_ptr);
		}
		return (2);
	}
	utils_putstr(STDOUT_FILENO, "Window created!\n");
	sleep(2);
	if (win_ptr)
		mlx_destroy_window(mlx_ptr, win_ptr);
	if (mlx_ptr)
	{
		mlx_destroy_display(mlx_ptr);
		free(mlx_ptr);
	}
	logger_destroy(logger);
	return (0);
}
