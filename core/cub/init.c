#include "../../includes/main.h"

bool	init_win(t_cub *cub)
{
	cub->win = (t_window *)malloc(sizeof(t_window));
	if (!cub->win)
	{
		ft_fprintf(STDERR_FILENO,
			"Error: Failed to allocate memory for window.\n");
		return (false);
	}
	return (true);
}

bool	init_mlx(t_cub *cub)
{
	cub->win->mlx = mlx_init();
	if (!cub->win->mlx)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to initialize mlx.\n");
		free(cub->win);
		return (false);
	}
	cub->win->win = mlx_new_window(cub->win->mlx, WIN_WIDTH, WIN_HEIGHT,
			"cub3D");
	if (!cub->win->win)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to create window.\n");
		free(cub->win);
		return (false);
	}
	return (true);
}

bool	init_map(t_cub *cub)
{
	cub->map = (t_map *)malloc(sizeof(t_map));
	if (!cub->map)
	{
		ft_fprintf(STDERR_FILENO,
			"Error: Failed to allocate memory for map.\n");
		free(cub->win->win);
		free(cub->win);
		return (false);
	}
	*cub->map = (t_map){.map = NULL, .floor = 0, .ceiling = 0, .no = NULL,
		.so = NULL, .we = NULL, .ea = NULL};
	return (true);
}

bool	init_image(t_cub *cub)
{
	cub->win->img->img = mlx_new_image(cub->win->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->win->img->img)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to create image.\n");
		free(cub->win->img);
		free(cub->map);
		free(cub->win->win);
		free(cub->win);
		return (false);
	}
	cub->win->img->addr = mlx_get_data_addr(cub->win->img->img,
			&cub->win->img->bpp, &cub->win->img->line_len,
			&cub->win->img->endian);
	if (!cub->win->img->addr)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to get image address.\n");
		mlx_destroy_image(cub->win->mlx, cub->win->img->img);
		free(cub->win->img);
		free(cub->map);
		free(cub->win->win);
		free(cub->win);
		return (false);
	}
	return (true);
}

bool	initialization(t_cub *cub)
{
	if (!init_win(cub))
		return (false);
	if (!init_mlx(cub))
		return (false);
	if (!init_map(cub))
		return (false);
	cub->win->img = (t_image *)malloc(sizeof(t_image));
	if (!cub->win->img)
	{
		ft_fprintf(STDERR_FILENO,
			"Error: Failed to allocate memory for image.\n");
		free(cub->map);
		free(cub->win->win);
		free(cub->win);
		return (false);
	}
	if (!init_image(cub))
		return (false);
	cub->win->img->width = WIN_WIDTH;
	cub->win->img->height = WIN_HEIGHT;
	return (true);
}
