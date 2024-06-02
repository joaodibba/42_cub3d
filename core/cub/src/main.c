#include "../inc/cub.h"
#include <errno.h>

// TODO: later change all printf to ft_printf
// ! No need to change printf to ft_printf because printf is allowd in the project

void	print_menu(void)
{
	printf("Move Player  : [UP (W) | DOWN (S) | LEFT (A) | RIGHT (D)]\n");
	printf("Rotate View  : [ARROW LEFT | ARROW RIGHT]\n");
    printf("Dimension ±  : [R]");
	printf("Exit         : [ESC]\n");
}

static bool	guard(int ac, char **av)
{
    if (ac == 2 && av[0] && av[1])
    	return (true);
	ft_fprintf(STDERR_FILENO, "Error: Invalid use.\n");
	ft_fprintf(STDERR_FILENO, "Uses: ./cub3D [path/to/map.ber]\n");
	return (false);
}

static bool initialization(t_window *win) 
{
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!win->win)
	{
		ft_fprintf(STDERR_FILENO, "Error: mlx initialization failed.\n");
		return (false);
	}
    return (true);
}

int	key_press(int key, t_controller *ctrl) 
{
	if (key == ESC)
		ctrl->game_over = true;
	if (key == UP || key == W)
		ctrl->mv_fw = true;
	if (key == DOWN || key == S)
		ctrl->mv_bw = true;
	if (key == LEFT || key == A)
		ctrl->mv_lf = true;
	if (key == RIGHT || key == D)
		ctrl->mv_rt = true;
    return (0);
}

int	key_release(int key, t_controller *ctrl) 
{
	if (key == ESC)
		ctrl->game_over = false;
	if (key == UP || key == W)
		ctrl->mv_fw = false;
	if (key == DOWN || key == S)
		ctrl->mv_bw = false;
	if (key == LEFT || key == A)
		ctrl->mv_lf = false;
	if (key == RIGHT || key == D)
		ctrl->mv_rt = false;
    return (0);
}

int	mouse_move(int x, int y, void *obj) 
{
    return (0);
}

int	exit_cub(t_window *win) 
{
	ft_fprintf(STDOUT_FILENO, "You exited Cub3D\n");
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
}

int	main(int argc, char **argv)
{
    t_window	*win;
	t_map		*map;
	t_controller *ctrl;

	win = (t_window *)malloc(sizeof(t_window));
	map = (t_map *)malloc(sizeof(t_map));
	// *map = (t_map){ .map = NULL, .floor = NULL, .ceiling = NULL, .no = NULL, .so = NULL, .we = NULL, .ea = NULL };
	map->ceiling = NULL;
	map->floor = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->map = NULL;
    if (!guard(argc, argv) || \
		!initialization(win))
		return (2);
    mlx_hook(win->win, 17, 0, &exit_cub, win);
    mlx_hook(win->win, 2, (1L << 0), &key_press, ctrl);
	mlx_hook(win->win, 3, (1L << 1), &key_release, ctrl);
	mlx_hook(win->win, 6, (1L << 6), &mouse_move, ctrl);
    print_menu();
    mlx_loop(win->mlx);
	return (0);
}