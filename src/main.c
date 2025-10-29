#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../minilibx-linux/mlx.h"


// destroy sirasi
// image, window, display

// man kurulumu
// manpath
//
// Sistem genelinde kurulum:
// sudo cp -r minilibx-linux/man/man1 /usr/local/share/man
// sudo cp -r minilibx-linux/man/man3 /usr/local/share/man
//
// man database guncelleme
// mandb

// git submodule eklemek icin
// git submodule add https://github.com/42paris/minilibx-linux

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s + len))
		len++;
	return (len);
}

void	ft_putstr(int fd, const char *s)
{
	size_t	len;

	len = ft_strlen(s);
	(void) write(fd, s, len);
}

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();

	if (!mlx_ptr)
	{
		ft_putstr(STDERR_FILENO, "mlx init failed!\n");
		return (1);
	}
	ft_putstr(STDOUT_FILENO, "mlx initialized!\n");
	win_ptr = mlx_new_window(mlx_ptr, 300, 300, "Selamu-Aleykum...");
	if (!win_ptr)
	{
		// TODO maybe garbage collecting in the future??
		ft_putstr(STDERR_FILENO, "Window create failed!\n");
		if (mlx_ptr)
		{
			mlx_destroy_display(mlx_ptr);
			free(mlx_ptr);
		}
		return (2);
	}
	ft_putstr(STDOUT_FILENO, "Window created!\n");
	sleep(2);

	// Cleanup
	if (win_ptr)
		mlx_destroy_window(mlx_ptr, win_ptr);
	if (mlx_ptr)
	{
		mlx_destroy_display(mlx_ptr);
		free(mlx_ptr);
	}
	return (0);
}
