/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:51:06 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/02 04:35:40 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	utils_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s + len))
		len++;
	return (len);
}

void	utils_putchar(int fd, const char c)
{
	write(fd, &c, 1);
}

void	utils_putstr(int fd, const char *s)
{
	size_t	len;

	len = utils_strlen(s);
	write(fd, s, len);
}

void	utils_put_unsigned_nb(int fd, unsigned int nb)
{
	char	buffer[12];
	int		i;

	if (nb < 10)
	{
		utils_putchar(fd, '0');
		utils_putchar(fd, '0' + nb);
		return ;
	}
	i = 0;
	while (nb > 0)
	{
		buffer[i++] = '0' + (nb % 10);
		nb /= 10;
	}
	while (i > 0)
		utils_putchar(fd, buffer[--i]);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(fd, "-2147483648", 11);
			return ;
		}
		utils_putchar(fd, '-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd((n / 10), fd);
		n = n % 10;
	}
	if (n < 10)
		write(fd, &("0123456789"[n]), 1);
}
