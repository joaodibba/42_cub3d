#include "../inc/cub.h"
#include <errno.h>

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

static bool initialization(t_window **win, t_map **map, t_controller *ctrl)
{
	*ctrl = (t_controller){ .mv_fw = false, .mv_bw = false, .mv_lf = false, .mv_rt = false, .rt_lf = false, .rt_rt = false, .game_over = false };
	*win = (t_window *)malloc(sizeof(t_window));
	if (!*win)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to allocate memory for window.\n");
		return (false);
	}
	(*win)->mlx = mlx_init();
	(*win)->win = mlx_new_window((*win)->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	*map = (t_map *)malloc(sizeof(t_map));
	if (!*map)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to allocate memory for map.\n");
		return (false);
	}
	**map = (t_map){ .map = NULL, .floor = NULL, .ceiling = NULL, .no = NULL, .so = NULL, .we = NULL, .ea = NULL };
    return (true);
}

int	exit_cub(t_window *win) 
{
	ft_fprintf(STDOUT_FILENO, "You exited Cub3D\n");
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
}

int	main(int argc, char **argv)
{
    t_window		*win = NULL;
	t_map			*map = NULL;
	t_controller	ctrl;

    if (!guard(argc, argv) || \
		!initialization(&win, &map, &ctrl))
		return (2);
    mlx_hook(win->win, 17, 0, &exit_cub, win);
    mlx_hook(win->win, 2, (1L << 0), &key_press, &ctrl);
	mlx_hook(win->win, 3, (1L << 1), &key_release, &ctrl);
	mlx_hook(win->win, 6, (1L << 6), &mouse_move, &ctrl);
    print_menu();
	// mlx_loop_hook(win->mlx, &render, win);
    mlx_loop(win->mlx);
	return (0);
}
