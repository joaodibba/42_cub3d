#include "../../includes/main.h"

// TODO: later change all printf to ft_printf
// ! No need to change printf to ft_printf because printf is allowed in the project

void	print_menu(void)
{
	printf("---------- CONTROLS ----------\n");
	printf(GREEN BOLD "Movements:\n" RESET_COLOR);
	printf("FORWARD     : [UP (W | ⬆)]\n");
	printf("BACK        : [DOWN (S | ⬇)]\n");
	printf("LEFT        : [A]\n");
	printf("RIGHT       : [D]\n\n");
	printf(GREEN BOLD "Rotatations :\n" RESET_COLOR);
	printf("LEFT        : [LEFT (Q | ⬅)]\n");
	printf("RIGHT       : [RIGHT (E | →)]\n\n");
	printf(GREEN BOLD "Others:\n" RESET_COLOR);
	printf("Exit        : [CLOSE (ESC)]\n");
	printf("------------------------------\n");
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

bool initialization(t_cub *cub);

int main(int argc, char **argv)
{
	static t_cub	*cub;

	cub = (t_cub *)malloc(sizeof(t_cub));
	if (!cub)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to allocate memory for cub.\n");
		return (2);
	}
	if (!guard(argc, argv) || !initialization(cub) || !parser(argv[1], cub->win, cub->map))
		return (2);
	cub->ctrl = init_controller(cub);
	if (!cub->ctrl)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to initialize controller.\n");
		free(cub);
		return (2);
	}
	init_player(&cub->player, cub->map);

	print_menu();
	mlx_loop_hook(cub->win->mlx, &cube_loop, cub);
	mlx_loop(cub->win->mlx);
	return (0);
}