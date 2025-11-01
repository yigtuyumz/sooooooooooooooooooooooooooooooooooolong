/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 08:26:17 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/01 22:57:22 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
# define LOGGER_H

# ifndef STDOUT_FILENO
#  define STDOUT_FILENO 1
# endif

# ifndef STDERR_FILENO
#  define STDERR_FILENO 2
# endif

# define LOGGER_FD_FALLBACK STDERR_FILENO

# define LOG_OUT  0b00000001
# define LOG_ERR  0b00000010
# define LOG_INFO 0b00000100
# define LOG_WARN 0b00001000

typedef struct s_logger
{
	int	fd_out;
	int	fd_err;
	int	fd_info;
	int	fd_warn;
}	t_logger;

int			open_fd(const char *path);
void		close_fd(int fildes);
t_logger	*logger_init(
				const char *out,
				const char *err,
				const char *info,
				const char *warn
				);
void		logger_destroy(t_logger *logger);

#endif
