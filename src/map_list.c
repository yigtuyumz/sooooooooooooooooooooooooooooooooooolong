/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:46:38 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 21:46:39 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

t_map_node	*create_node(char *line)
{
	t_map_node	*node;

	node = malloc(sizeof(t_map_node));
	if (!node)
		return (NULL);
	node->line = line;
	node->next = NULL;
	return (node);
}

void	free_list(t_map_node *head)
{
	t_map_node	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free((void *) tmp->line);
		free((void *) tmp);
	}
}

char	**list_to_array(t_map_node *head, int rows)
{
	char	**grid;
	int		i;

	grid = malloc(sizeof(char *) * (rows + 1));
	if (!grid)
		return (NULL);
	i = 0;
	while (head)
	{
		grid[i] = head->line;
		head->line = NULL;
		head = head->next;
		i++;
	}
	grid[i] = NULL;
	return (grid);
}
