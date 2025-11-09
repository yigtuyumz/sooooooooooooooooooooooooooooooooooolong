/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:51:03 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 17:33:22 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

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

size_t		utils_strlen(const char *s);
void		utils_putstr(int fd, const char *s);
void		utils_putchar(int fd, const char c);
int			utils_endswith(const char *str, const char *val);
char		*utils_strdup(const char *s);
//void		utils_putdate(int fd);

char		*get_next_line(int fd);

// void		*utils_memset(void *s, int c, size_t n);

#endif
