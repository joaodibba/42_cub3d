#include "../../includes/main.h"

// TODO: later change all printf to ft_printf
// ! No need to change printf to ft_printf because printf is allowed in the project

void	print_menu(void)
{
	printf("Move Player  : [UP (W) | DOWN (S) | LEFT (A) | RIGHT (D)]\n");
	printf("Rotate View  : [ARROW LEFT | ARROW RIGHT]\n");
	printf("Dimension ±  : [R]\n");
	printf("Exit         : [ESC]\n");
}

static bool	guard(int ac, char **av)
{
	if (ac == 2 && av[0] && av[1])
		return (true);
	ft_fprintf(STDERR_FILENO, "Error: Invalid use.\n");
	ft_fprintf(STDERR_FILENO, "Usage: ./cub3D [path/to/map.ber]\n");
	return (false);
}

void    update_camera_plane(t_player *player);

int cube_loop(t_cub *cub)
{
	player_move(&cub->player, cub->ctrl, cub->map->map);
	paint_window(cub->win, cub->map->ceiling, cub->map->floor);
    update_camera_plane(&cub->player);
	render_dimension_3d(cub);
	render_2d_map(cub, cub->map, cub->win, cub->player);
	mlx_put_image_to_window(cub->win->mlx, cub->win->win, cub->win->img->img, 0, 0);
	return (0);
}

bool initialization(t_window **win, t_map **map);

int main(int argc, char **argv)
{
    t_window        *win = NULL;
    t_map           *map = NULL;
    t_cub           *cub;
    t_controller    *ctrl;

    if (!guard(argc, argv) || !initialization(&win, &map) || !parser(argv[1], win, map))
        return (2);
    cub = (t_cub *)malloc(sizeof(t_cub));
    if (!cub)
    {
        ft_fprintf(STDERR_FILENO, "Error: Failed to allocate memory for cub.\n");
        return (2);
    }
    cub->win = win;
    cub->map = map;
    cub->ctrl = NULL;
    cub->ctrl = init_controller(cub);
	if (!cub->ctrl)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to initialize controller.\n");
		free(cub);
		return (2);
	}
	init_player(&cub->player, map);

	print_menu();
    mlx_loop_hook(win->mlx, &cube_loop, cub);
    mlx_loop(win->mlx);

    ft_free_array(map->map);
    free(map);
    free(win);
    free(cub->ctrl);
    free(cub);
    return (0);
}