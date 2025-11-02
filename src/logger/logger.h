/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 08:26:17 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/02 01:07:47 by yuyumaz          ###   ########.fr       */
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

# define LOGGER_OUT "out.log"
# define LOGGER_ERR "err.log"
# define LOGGER_FD_FALLBACK STDERR_FILENO

typedef struct s_logger
{
	int		errfile;
	int		outfile;
	void	(*hook)(void *arg);
}	t_logger;

int			open_logfile(const char *path);
void		close_logfile(int fd);
t_logger	*init_logger(void (*init_hook)(void *arg));
void		destroy_logger(t_logger **logger, void (*cleanup_hook)(void *arg));
#endif
