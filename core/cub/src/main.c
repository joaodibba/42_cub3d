#include "../inc/cub.h"


void	print_menu(void)
{
	ft_printf("Move Player  : [UP (W) | DOWN (S) | LEFT (A) | RIGHT (D)]\n");
	ft_printf("Rotate View  : [ARROWS (LEFT|RIGHT)]\n");
	ft_printf("Exit         : [ESC]\n");
}

bool _valid_map(char *path) {
    return true;
}

bool	guard(int ac, char **av)
{
    if (ac == 2 && _valid_map(av[1]))
        return (true);

    ft_printf("Invalid number of arguments!!\n");
    ft_printf("Uses: ./cub3D [PATH TO MAP]\n");
    return (false);
}

bool initialization() {
    return (true);
}

void *key_hooks(int key_pressed, void *obj) {
    return (NULL);
}

void *mouse_hooks(int x, int y, void *obj) {
    return (NULL);
}

void *exit_fractal() {
    return (NULL);
}

int	main(int argc, char **argv)
{
    t_window win;

    if (!guard(argc, argv))
        return (1);

    if (!initialization())
        return (ft_printf("ERROR: Failed to initialize program!\n"));

    mlx_hook(win.win, CROSS, 0, exit_fractal, NULL);
    mlx_key_hook(win.win, key_hooks, NULL);
    mlx_mouse_hook(win.win, mouse_hooks, NULL);
    print_menu();
    mlx_loop(win.mlx);
	return (0);
}