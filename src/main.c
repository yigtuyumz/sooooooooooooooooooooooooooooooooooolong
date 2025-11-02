/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 08:22:37 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/02 05:08:40 by yuyumaz          ###   ########.fr       */
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

void	logger_init_hook(void *arg)
{
	t_logger	*logger;

	logger = (t_logger *) arg;
	logger->errfile = open_logfile("err.log");
	logger->outfile = open_logfile("out.log");
	utils_putstr(logger->outfile, "\n\n");
	utils_putdate(logger->outfile);
	if (logger->outfile != LOGGER_FD_FALLBACK)
	{
		utils_putstr(logger->outfile,
			"============== LOGGER INITIALIZED ============\n");
	}
	else
		utils_putstr(logger->outfile,
			"LOGGER INIT FAILED, OUTPUTS TO STDERR\n");
}

void	logger_destroy_hook(void *arg)
{
	t_logger	*logger;

	logger = (t_logger *) arg;
	utils_putdate(logger->outfile);
	utils_putstr(logger->outfile,
		"============== LOGGER SHUTDOWN ==============\n");
}

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
	t_logger	*logger;

	logger = init_logger(logger_init_hook);
	create_mlx_window(logger);
	utils_putstr(logger->outfile, "LOG = WOOD ?\n");
	destroy_logger(&logger, logger_destroy_hook);
	return (0);
}
