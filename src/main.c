/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 08:22:37 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/03 20:40:17 by yuyumaz          ###   ########.fr       */
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

void	destroy_mlx_window(void *mlx_ptr, void *win_ptr)
{
	if (win_ptr)
		mlx_destroy_window(mlx_ptr, win_ptr);
	if (mlx_ptr)
	{
		mlx_destroy_display(mlx_ptr);
		free(mlx_ptr);
	}
}

void	create_mlx_window(t_logger *logger)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
	{
		utils_putstr(logger->outfile, "mlx init failed!\n");
		exit(EXIT_FAILURE);
	}
	utils_putstr(logger->outfile, "mlx initialized!\n");
	win_ptr = mlx_new_window(mlx_ptr, 300, 300, "Hello, World!");
	if (!win_ptr)
	{
		utils_putstr(logger->outfile, "Window create failed!\n");
		if (mlx_ptr)
		{
			mlx_destroy_display(mlx_ptr);
			free(mlx_ptr);
		}
		exit(EXIT_FAILURE);
	}
	utils_putstr(logger->outfile, "Window created!\n");
	sleep(2);
	destroy_mlx_window(mlx_ptr, win_ptr);
}

// TODO: add LOGGER.log method, which displays timestamp in each log
int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	t_logger_config	config;
	t_logger		*logger;

	config.outfile_path = "out.log";
	config.errfile_path = "err.log";
	config.flags = 0;
	logger = init_logger(&config);
	if (!logger)
	{
		utils_putstr(STDERR_FILENO, "Logger init failed!\n");
		return (1);
	}
	utils_putstr(logger->outfile, "\n\n");
	utils_putdate(logger->outfile);
	utils_putstr(logger->outfile, "LOGGER INITIALIZED\n");
	create_mlx_window(logger);
	utils_putstr(logger->outfile, "LOG = WOOD ?\n");
	utils_putdate(logger->outfile);
	utils_putstr(logger->outfile, "LOGGER SHUTDOWN\n");
	destroy_logger(&logger);
	return (0);
}
