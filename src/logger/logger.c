/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 08:26:29 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/10/29 08:26:36 by yuyumaz          ###   ########.fr       */
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
	fd = open(path, O_RDONLY | O_CREAT);
	if (fd < 0)
		return (LOGGER_FD_FALLBACK);
	return (fd);
}

t_logger	*logger_init(const char **list)
{
	t_logger	*logger;

	logger = (t_logger *) malloc(sizeof(t_logger));
	if (!logger)
		return (NULL);
	logger->fd_out = open_fd(list[0]);
	logger->fd_err = open_fd(list[1]);
	logger->fd_info = open_fd(list[2]);
	logger->fd_warn = open_fd(list[3]);
	return (logger);
}

ssize_t	wood(int fd, const char *msg)
{
	return (write(fd, msg, 1));	//! TODO IMPLEMENT ME
}
