/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:46:42 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 21:46:44 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	add_line_to_list(t_map_node **head, t_map_node **tail, char *line)
{
	t_map_node	*new_node;

	new_node = create_node(line);
	if (!new_node)
	{
		free_list(*head);
		return (0);
	}
	if (!*head)
		*head = new_node;
	else
		(*tail)->next = new_node;
	*tail = new_node;
	return (1);
}

t_map_node	*read_to_list(int fd, int *row_count)
{
	t_map_node	*head;
	t_map_node	*tail;
	char		*line;

	head = NULL;
	tail = NULL;
	*row_count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!add_line_to_list(&head, &tail, line))
			return (NULL);
		(*row_count)++;
	}
	return (head);
}
