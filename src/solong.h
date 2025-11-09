/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 02:22:11 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 17:58:01 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include <stdlib.h>
# include "utils.h"
# include "mlx.h"
# include "ft_fprintf.h"

# define PIXEL_BLACK 0x00000000
# define PIXEL_RED   0x00FF0000
# define PIXEL_GREEN 0x0000FF00
# define PIXEL_BLUE  0x000000FF

# define WIN_WIDTH 300
# define WIN_HEIGHT 300
# define WIN_NAME "So f****** long!"

typedef struct s_map_node
{
	char				*line;
	struct s_map_node	*next;
}	t_map_node;

typedef struct s_map
{
	const char		*path;
	int				fd;
	char			**grid;
	int				rows;
	int				cols;
	int				player_x;
	int				player_y;
	int				exit_x;
	int				exit_y;
	int				collectibles;
}	t_map;

typedef struct s_window
{
	void		*win_ptr;
	const char	*name;
	int			width;
	int			height;
}	t_window;

typedef struct s_app
{
	void			*mlx_ptr;
	t_window		*window;
	t_map			*map;
}	t_app;

void	*alloc_window(t_app **app);
void	free_window(t_app **app);
void	*alloc_map(t_app **app);
void	free_map(t_app **app);
void	*free_app(t_app **app);
t_app	*alloc_app(void);
int		map_read(t_map *map, const char *path);
int		map_validate(t_map *map);
int		map_check_extension(const char *path);
int		map_check_file_exists(const char *path);

#endif
