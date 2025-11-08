/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:51:06 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/07 21:56:53 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

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

int	utils_endswith(const char *str, const char *val)
{
	size_t	len_str;
	size_t	len_val;
	size_t	i;

	len_str = utils_strlen(str);
	len_val = utils_strlen(val);
	if (len_val > len_str)
		return (0);
	i = 0;
	while (i < len_val)
	{
		if (*(str + len_str - len_val + i) != *(val + i))
			return (0);
		i++;
	}
	return (1);
}

char	*utils_strdup(const char *s)
{
	size_t	str_len;
	size_t	iter;
	char	*ret;

	str_len = utils_strlen(s);
	ret = (char *) malloc(sizeof(char) * (str_len + 1));
	if (!ret)
		return (NULL);
	iter = 0;
	while (iter < str_len)
	{
		*(ret + iter) = *(s + iter);
		iter++;
	}
	*(ret + iter) = 0;
	return (ret);
}
