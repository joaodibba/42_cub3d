#include "../../includes/main.h"

void    destroy_image(void *mlx, t_image *img)
{
    if (!mlx || !img || !img->img)
        return;
    mlx_destroy_image(mlx, img->img);
    if (img)
        free(img);
}

void	destroy_map(void *mlx, t_map	*map)
{

    if (!mlx || !map)
        return;
    destroy_image(mlx, map->no);
    destroy_image(mlx, map->so);
    destroy_image(mlx, map->we);
    destroy_image(mlx, map->ea);
	if (map->map)
		ft_free_array(map->map);
	if (map)
		free(map);
}

void	destroy_window(t_window *win)
{
	destroy_image(win->mlx, win->img);
	mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_display(win->mlx);
	if (win->mlx)
		free(win->mlx);
	if (win)
		free(win);
}

void	free_cub(t_cub *cub)
{
    if (cub->map)
	    destroy_map(cub->win->mlx, cub->map);
    if (cub->win)
	    destroy_window(cub->win);
	if (cub->ctrl)
		free(cub->ctrl);
	if (cub)
		free(cub);
}

int	exit_cub(t_cub *cub)
{
	ft_fprintf(STDOUT_FILENO, "You exited Cub3D\n");
	free_cub(cub);
	exit(0);
}