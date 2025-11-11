/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyumaz <yuyumaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:45:29 by yuyumaz           #+#    #+#             */
/*   Updated: 2025/11/09 21:58:51 by yuyumaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "solong.h"

int	main(int argc, char *argv[])
{
	t_app	*app;

	if (!validate_args(argc, argv))
		exit(EXIT_FAILURE);
	app = alloc_app();
	if (!app)
		exit(EXIT_FAILURE);
	if (!load_and_validate_map(app, argv[1]))
	{
		free_app(&app);
		exit(EXIT_FAILURE);
	}
	if (!init_app(app))
	{
		free_app(&app);
		exit(EXIT_FAILURE);
	}
	render_map(app);
	sleep(2);
	free_app(&app);
	return (0);
}
