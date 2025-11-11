/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:46:53 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 21:58:49 by yuyumaz          ###   ########.fr       */
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

# define WIN_WIDTH 480
# define WIN_HEIGHT 480
# define BASE_TILE_SIZE 48
# define WIN_NAME "So f****** long!"

typedef struct s_map_node
{
	char				*line;
	struct s_map_node	*next;
}	t_map_node;

typedef struct s_game
{
	int		moves;
	int		collected;
	int		player_x;
	int		player_y;
	int		finished;
}	t_game;

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
	int			tile_width;
	int			tile_height;
}	t_window;

typedef struct s_app
{
	void			*mlx_ptr;
	t_window		*window;
	t_map			*map;
	t_game			*game;
}	t_app;

void		*alloc_window(t_app **app);
void		free_window(t_app **app);
void		*alloc_map(t_app **app);
void		free_map(t_app **app);
void		*alloc_game(t_app **app);
void		free_game(t_app **app);
void		*free_app(t_app **app);
t_app		*alloc_app(void);
int			map_read(t_map *map, const char *path);
int			map_validate(t_map *map);
int			map_check_extension(const char *path);
int			map_check_file_exists(const char *path);
int			check_rectangular(t_map *map);
int			check_walls(t_map *map);
int			check_elements(t_map *map);
int			check_path(t_map *map);
int			validate_args(int argc, char *argv[]);
int			init_app(t_app *app);
int			load_and_validate_map(t_app *app, const char *path);
t_map_node	*create_node(char *line);
void		free_list(t_map_node *head);
char		**list_to_array(t_map_node *head, int rows);
t_map_node	*read_to_list(int fd, int *row_count);
void		render_map(t_app *app);

#endif
