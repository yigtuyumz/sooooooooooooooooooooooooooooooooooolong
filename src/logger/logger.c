/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 08:26:29 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/02 04:19:52 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "logger.h"

// Heavily inspired the concept of `Dependency Injection`.
// https://devmethodologies.blogspot.com/2012/07/dependency-injection.html
// And the design of lib logger, kinda includes it.
int	open_logfile(const char *path)
{
	int	fd;

	if (!path)
		return (LOGGER_FD_FALLBACK);
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (LOGGER_FD_FALLBACK);
	return (fd);
}

void	close_logfile(int fd)
{
	if (fd > 2)
		(void) close(fd);
}

t_logger	*init_logger(void (*init_hook)(void *arg))
{
	t_logger	*logger;

	logger = (t_logger *) malloc(sizeof(t_logger));
	if (!logger)
		return (NULL);
	logger->errfile = LOGGER_FD_FALLBACK;
	logger->outfile = LOGGER_FD_FALLBACK;
	if (init_hook)
		init_hook((void *) logger);
	return (logger);
}

void	destroy_logger(t_logger **logger, void (*cleanup_hook)(void *arg))
{
	if (!logger || !(*logger))
		return ;
	if (cleanup_hook)
		cleanup_hook((void *) *logger);
	close_logfile((*logger)->errfile);
	close_logfile((*logger)->outfile);
	free(*logger);
	*logger = NULL;
}
