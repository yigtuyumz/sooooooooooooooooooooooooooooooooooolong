/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:38:04 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 20:05:16 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include <fcntl.h>
#include <unistd.h>

int	map_check_extension(const char *path)
{
	if (!path)
		return (0);
	if (!utils_endswith(path, ".ber"))
		return (0);
	return (1);
}

int	map_check_file_exists(const char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static t_map_node	*create_node(char *line)
{
	t_map_node	*node;

	node = malloc(sizeof(t_map_node));
	if (!node)
		return (NULL);
	node->line = line;
	node->next = NULL;
	return (node);
}

static void	free_list(t_map_node *head)
{
	t_map_node	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->line);
		free(tmp);
	}
}

static t_map_node	*read_to_list(int fd, int *row_count)
{
	t_map_node	*head;
	t_map_node	*tail;
	t_map_node	*new_node;
	char		*line;

	head = NULL;
	tail = NULL;
	*row_count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		new_node = create_node(line);
		if (!new_node)
		{
			free_list(head);
			return (NULL);
		}
		if (!head)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		(*row_count)++;
	}
	return (head);
}

static char	**list_to_array(t_map_node *head, int rows)
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

int	map_read(t_map *map, const char *path)
{
	t_map_node	*list;
	int			fd;
	int			i;
	int			len;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	list = read_to_list(fd, &map->rows);
	(void) close(fd);
	if (!list)
		return (0);
	map->grid = list_to_array(list, map->rows);
	free_list(list);
	if (!map->grid)
		return (0);
	i = -1;
	while (++i < map->rows)
	{
		len = utils_strlen(map->grid[i]);
		if (len > 0 && map->grid[i][len - 1] == '\n')
			map->grid[i][len - 1] = '\0';
	}
	if (map->rows > 0)
		map->cols = utils_strlen(map->grid[0]);
	else
		map->cols = 0;
	return (1);
}
