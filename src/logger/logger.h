/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 08:26:17 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/03 20:37:01 by yuyumaz          ###   ########.fr       */
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

typedef struct s_logger_config
{
	const char	*outfile_path;
	const char	*errfile_path;
	int			flags;
}	t_logger_config;

typedef struct s_logger
{
	int		errfile;
	int		outfile;
}	t_logger;

t_logger	*init_logger(t_logger_config *config);
void		destroy_logger(t_logger **logger);
#endif
