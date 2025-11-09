/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:46:17 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 21:46:19 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"
#include <unistd.h>

int	validate_args(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_fprintf(STDERR_FILENO, "Error\nUsage: %s <map.ber>\n", argv[0]);
		return (0);
	}
	if (!map_check_extension(argv[1]))
	{
		ft_fprintf(STDERR_FILENO,
			"Error\nMap file must have .ber extension\n");
		return (0);
	}
	if (!map_check_file_exists(argv[1]))
	{
		ft_fprintf(STDERR_FILENO,
			"Error\nCannot open map file: %s\n", argv[1]);
		return (0);
	}
	return (1);
}
