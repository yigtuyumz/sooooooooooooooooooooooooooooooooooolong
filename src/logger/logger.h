/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 08:26:17 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/10/31 18:54:03 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
# define LOGGER_H

# include <stddef.h>

# ifndef STDOUT_FILENO
#  define STDOUT_FILENO 1
# endif

# ifndef STDERR_FILENO
#  define STDERR_FILENO 2
# endif

# define LOGGER_FD_FALLBACK STDERR_FILENO

typedef struct s_logger
{
	int	fd_out;
	int	fd_err;
	int	fd_info;
	int	fd_warn;

}	t_logger;

int		open_fd(const char *path);
t_logger	*logger_init(const char **list);
ssize_t		wood(int fd, const char *msg);


#endif
