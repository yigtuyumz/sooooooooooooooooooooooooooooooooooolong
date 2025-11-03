/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 08:26:29 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/03 20:36:57 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "logger.h"

static int	open_logfile(const char *path)
{
	int	fd;

	if (!path)
		return (LOGGER_FD_FALLBACK);
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (LOGGER_FD_FALLBACK);
	return (fd);
}

static void	close_logfile(int fd)
{
	if (fd > 2)
		(void) close(fd);
}

t_logger	*init_logger(t_logger_config *config)
{
	t_logger	*logger;

	logger = (t_logger *) malloc(sizeof(t_logger));
	if (!logger)
		return (NULL);
	if (config)
	{
		logger->outfile = open_logfile(config->outfile_path);
		logger->errfile = open_logfile(config->errfile_path);
	}
	else
	{
		logger->outfile = LOGGER_FD_FALLBACK;
		logger->errfile = LOGGER_FD_FALLBACK;
	}
	return (logger);
}

void	destroy_logger(t_logger **logger)
{
	if (!logger || !(*logger))
		return ;
	close_logfile((*logger)->errfile);
	close_logfile((*logger)->outfile);
	free(*logger);
	*logger = NULL;
}
