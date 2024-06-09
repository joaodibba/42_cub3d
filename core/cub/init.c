#include "../../includes/main.h"

bool initialization(t_window **win, t_map **map)
{
	*win = (t_window *)malloc(sizeof(t_window));
	if (!*win)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to allocate memory for window.\n");
		return (false);
	}
	(*win)->mlx = mlx_init();
	if (!(*win)->mlx)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to initialize mlx.\n");
		free(*win);
		return (false);
	}
	(*win)->win = mlx_new_window((*win)->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!(*win)->win)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to create window.\n");
		free(*win);
		return (false);
	}

	*map = (t_map *)malloc(sizeof(t_map));
	if (!*map)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to allocate memory for map.\n");
		free(*win);
		return (false);
	}
	**map = (t_map){ .map = NULL, .floor = 0, .ceiling = 0, .no = NULL, .so = NULL, .we = NULL, .ea = NULL };
	(*win)->img = (t_image *)malloc(sizeof(t_image));
	if (!(*win)->img)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to allocate memory for image.\n");
		free(*win);
		free(*map);
		return (false);
	}
	(*win)->img->img = mlx_new_image((*win)->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!(*win)->img->img)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to create image.\n");
		free(*win);
		free(*map);
		free((*win)->img);
		return (false);
	}
	(*win)->img->addr = mlx_get_data_addr((*win)->img->img, &(*win)->img->bpp, &(*win)->img->line_len, &(*win)->img->endian);
	if (!(*win)->img->addr)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to get image address.\n");
		free(*win);
		free(*map);
		free((*win)->img);
		return (false);
	}
	(*win)->img->width = WIN_WIDTH;
	(*win)->img->height = WIN_HEIGHT;
	return (true);
}