/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:58:23 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/08 06:39:19 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include "ft_fprintf.h"

static void	ft_putchar(t_printf *data, int c)
{
	if (data->written == -1)
		return ;
	else if (write(data->fd, &c, 1) == -1)
		data->written = -1;
	else
		data->written++;
}

static void	ft_putbase(t_printf *data, uint64_t nb, uint8_t base, uint8_t fmt)
{
	int		c;
	uint8_t	digit;

	if (base < 2 || base > 36)
		return ;
	if (fmt == 'd' || fmt == 'i')
	{
		if (((int64_t) nb) < 0)
		{
			ft_putchar(data, '-');
			nb = (uint64_t)(-((int64_t) nb));
		}
	}
	if (nb >= base)
		ft_putbase(data, nb / base, base, fmt);
	digit = nb % base;
	if (digit < 10)
		c = '0' + digit;
	else
		c = ((fmt >= 97 && fmt <= 122) * 32) + digit + 55;
	ft_putchar(data, c);
}

static void	ft_putstr(t_printf *data, char *str, int fmt)
{
	if (!str)
	{
		ft_putchar(data, '(');
		ft_putchar(data, 'n');
		if (fmt == 'p')
			ft_putchar(data, 'i');
		else
		{
			ft_putchar(data, 'u');
			ft_putchar(data, 'l');
		}
		ft_putchar(data, 'l');
		ft_putchar(data, ')');
		return ;
	}
	if (fmt == 'p')
	{
		ft_putchar(data, '0');
		ft_putchar(data, 'x');
		ft_putbase(data, (uint64_t)str, 16, fmt);
		return ;
	}
	while (*str && data->written != -1)
		ft_putchar(data, *(str++));
}

static void	handle_format(t_printf *data)
{
	if (*(data->fmt) == 'c')
		ft_putchar(data, va_arg(data->ap, int));
	else if (*(data->fmt) == 's' || *(data->fmt) == 'p')
		ft_putstr(data, va_arg(data->ap, char *), *(data->fmt));
	else if (*(data->fmt) == 'd' || *(data->fmt) == 'i')
		ft_putbase(data, va_arg(data->ap, int), 10, *(data->fmt));
	else if (*(data->fmt) == 'u')
		ft_putbase(data, va_arg(data->ap, unsigned int), 10, *(data->fmt));
	else if (*(data->fmt) == 'x' || *(data->fmt) == 'X')
		ft_putbase(data, va_arg(data->ap, unsigned int), 16, *(data->fmt));
	else if (*(data->fmt) == '%')
		ft_putchar(data, '%');
	else
	{
		ft_putchar(data, '%');
		ft_putchar(data, *(data->fmt));
	}
}

int	ft_fprintf(int fd, const char *fmt, ...)
{
	t_printf	data;

	if (!fmt)
		return (-1);
	data.fd = fd;
	data.fmt = fmt;
	data.written = 0;
	va_start(data.ap, fmt);
	while (*(data.fmt) && data.written != -1)
	{
		if (*(data.fmt) == '%' && *(data.fmt + 1))
		{
			data.fmt++;
			handle_format(&data);
		}
		else
			ft_putchar(&data, *(data.fmt));
		data.fmt++;
	}
	va_end(data.ap);
	return (data.written);
}
