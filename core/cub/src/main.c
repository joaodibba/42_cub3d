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

static bool initialization(t_window **win, t_map **map)
{
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

int	main(int argc, char **argv)
{
    t_window		*win = NULL;
	t_map			*map = NULL;
	t_controller	ctrl;

    if (!guard(argc, argv) || \
		!initialization(&win, &map))
		return (2);
	ctrl = init_controller(&win);
    print_menu();
	// mlx_loop_hook(win->mlx, &render, win);
    mlx_loop(win->mlx);
	return (0);
}
