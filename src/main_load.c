/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:46:02 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 21:46:14 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include <unistd.h>

int	load_and_validate_map(t_app *app, const char *path)
{
	if (!map_read(app->map, path))
	{
		ft_fprintf(STDERR_FILENO, "Error\nFailed to read map!\n");
		return (0);
	}
	if (!map_validate(app->map))
		return (0);
	return (1);
}
