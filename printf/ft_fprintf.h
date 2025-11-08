/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:58:10 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/08 06:24:54 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <stdarg.h>

typedef struct s_printf
{
	const char		*fmt;
	va_list			ap;
	int				fd;
	int				written;
}	t_printf;

int	ft_fprintf(int fd, const char *fmt, ...);

#endif
