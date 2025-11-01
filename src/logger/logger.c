/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 08:26:29 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/01 23:07:47 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "logger.h"

int	open_fd(const char *path)
{
	int	fd;

	if (!path)
		return (LOGGER_FD_FALLBACK);
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (LOGGER_FD_FALLBACK);
	return (fd);
}

void	close_fd(int fildes)
{
	if (fildes > LOGGER_FD_FALLBACK)
		(void) close(fildes);
}

t_logger	*logger_init(const char *out, const char *err, const char *info, const char *warn)
{
	t_logger	*logger;

	logger = (t_logger *) malloc(sizeof(t_logger));
	if (!logger)
		return (NULL);
	logger->fd_out = open_fd(out);
	logger->fd_err = open_fd(err);
	logger->fd_info = open_fd(info);
	logger->fd_warn = open_fd(warn);
	return (logger);
}

void	logger_destroy(t_logger *logger)
{
	if (!logger)
		return ;
	close_fd(logger->fd_out);
	close_fd(logger->fd_err);
	close_fd(logger->fd_info);
	close_fd(logger->fd_warn);
	free(logger);
}
