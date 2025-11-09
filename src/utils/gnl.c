/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:40:57 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 17:40:58 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "gnl.h"

static void	*freeall(void *area1, void *area2, void *area3)
{
	if (area1)
		free(area1);
	if (area2)
		free(area2);
	if (area3)
		free(area3);
	return ((void *)0);
}

static char	*save_rest(char *buf)
{
	int		i;
	char	*rest;

	i = 0;
	if (!buf[i])
		return (freeall(buf, NULL, NULL));
	while (buf[i] && buf[i] != '\n')
		i++;
	rest = ft_strdup(buf + i + (buf[i] == '\n'));
	freeall(buf, NULL, NULL);
	return (rest);
}

static char	*extract_line(char *buf)
{
	char	*line;
	int		i;

	i = 0;
	if (!buf || !buf[0])
		return ((void *)0);
	while (buf[i] && buf[i] != '\n')
		i++;
	i += (buf[i] == '\n');
	line = ft_substr(buf, 0, i);
	return (line);
}

static char	*read_line(int fd, char *buf)
{
	char	*tmp;
	ssize_t	r;

	tmp = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return ((void *)0);
	if (!buf)
		buf = ft_strdup("");
	if (!buf)
		return ((void *)0);
	while (!ft_strchr(buf, '\n'))
	{
		r = read(fd, tmp, BUFFER_SIZE);
		if (r == -1)
			return (freeall(buf, tmp, NULL));
		if (r <= 0)
			break ;
		tmp[r] = 0;
		buf = ft_strjoin(buf, tmp);
		if (!buf)
			return (freeall(buf, tmp, NULL));
	}
	freeall(tmp, NULL, NULL);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*bufs[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return ((void *)0);
	bufs[fd] = read_line(fd, bufs[fd]);
	if (!bufs[fd])
		return ((void *)0);
	line = extract_line(bufs[fd]);
	bufs[fd] = save_rest(bufs[fd]);
	return (line);
}
