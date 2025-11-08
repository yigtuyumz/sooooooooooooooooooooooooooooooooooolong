/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:51:03 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/08 09:32:28 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

# define LOGGER_FD_FALLBACK STDERR_FILENO

typedef struct s_mydate
{
	int				year;
	int				month;
	int				day;
	int				hour;
	int				minute;
	int				second;
	int				usecond;
}	t_mydate;

typedef struct s_logger_config
{
	const char	*outfile_path;
	const char	*errfile_path;
}	t_logger_config;

typedef struct s_logger
{
	int	(*out)(int fd, const char *msg, ...);
	int	(*err)(int fd, const char *msg, ...);
	int	outfd;
	int	errfd;
}	t_logger;

size_t		utils_strlen(const char *s);
void		utils_putstr(int fd, const char *s);
void		utils_putchar(int fd, const char c);
void		utils_putdate(int fd);
int			utils_endswith(const char *str, const char *val);
char		*utils_strdup(const char *s);

void		*utils_memset(void *s, int c, size_t n);

t_logger	*init_logger(t_logger_config *config);
void		destroy_logger(t_logger **logger);
void		config_logger(t_logger *logger, t_logger_config *new_config);

#endif
