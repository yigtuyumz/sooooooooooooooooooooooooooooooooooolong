/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 08:26:29 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/08 07:05:49 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"
#include "../../printf/ft_fprintf.h"

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

void	config_logger(t_logger *logger, t_logger_config *new_config)
{
	if (!logger || !new_config)
		return ;
	if (logger->outfd > 2)
		(void) close(logger->outfd);
	logger->outfd = open_logfile(new_config->outfile_path);
	if (logger->errfd > 2)
		(void) close(logger->errfd);
	logger->errfd = open_logfile(new_config->errfile_path);
}

t_logger	*init_logger(t_logger_config *config)
{
	t_logger	*logger;

	logger = (t_logger *) malloc(sizeof(t_logger));
	if (!logger)
		return (NULL);
	if (config)
	{
		logger->outfd = open_logfile(config->outfile_path);
		logger->errfd = open_logfile(config->errfile_path);
	}
	else
	{
		logger->outfd = LOGGER_FD_FALLBACK;
		logger->errfd = LOGGER_FD_FALLBACK;
	}
	logger->out = ft_fprintf;
	logger->err = ft_fprintf;
	return (logger);
}

void	destroy_logger(t_logger **logger)
{
	if (!logger || !(*logger))
		return ;
	if ((*logger)->errfd > 2)
		(void) close((*logger)->errfd);
	if ((*logger)->outfd > 2)
		(void) close((*logger)->outfd);
	(*logger)->err = NULL;
	(*logger)->out = NULL;
	(*logger)->outfd = -1;
	(*logger)->errfd = -1;
	free((void *) *logger);
	*logger = NULL;
}
