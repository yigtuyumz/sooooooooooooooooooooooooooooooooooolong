/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:51:03 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/02 04:32:10 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>

typedef struct s_mydate
{
	int	year;
	int	month;
	int	day;
	int	hour;
	int	minute;
	int	second;
	int	usecond;
}	t_mydate;

size_t	utils_strlen(const char *s);
void	utils_putstr(int fd, const char *s);
void	utils_putchar(int fd, const char c);
void	utils_put_unsigned_nb(int fd, unsigned int nb);
void	utils_putdate(int fd);
#endif
