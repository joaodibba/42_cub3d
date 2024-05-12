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
	ft_putendl_fd("Error: Invalid use.", STDERR_FILENO);
	ft_putendl_fd("Uses: ./cub3D [path/to/map.ber]", STDERR_FILENO);
	return (false);
}

// intialize the window
static bool initialization(t_window *win) 
{
	win->mlx = mlx_init();
	if (!win->mlx)
	{
		ft_putendl_fd("Error: Failed to initialize mlx.", STDERR_FILENO);
		return (false);
	}
	win->win = mlx_new_window(win->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!win->win)
	{
		ft_putendl_fd("Error: Failed to create window.", STDERR_FILENO);
		return (false);
	}
    return (true);
}

void *key_hooks(int key_pressed, void *obj) 
{
    return (NULL);
}

void *mouse_hooks(int x, int y, void *obj) 
{
    return (NULL);
}

void *exit_cub(void *obj) {
    return (NULL);
}

int	main(int argc, char **argv)
{
	char		**map;
    t_window	win;
	t_map		game_map;

    if (!guard(argc, argv) || \
		!initialization(&win) || \
		!parser(argv[1], &win, &map))
		return (2);
    mlx_hook(win.win, CROSS, 0, &exit_cub, NULL); // mlx hook to exit the program using the red cross button on the window
    mlx_key_hook(win.win, &key_hooks, NULL); // mlx hook to handle key press events
    mlx_mouse_hook(win.win, &mouse_hooks, NULL); // mlx hook to handle mouse events
    print_menu();
    mlx_loop(win.mlx);
	return (0);
}