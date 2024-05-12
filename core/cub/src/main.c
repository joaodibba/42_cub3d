#include "../inc/cub.h"


// TODO: later change all printf to ft_printf
void	print_menu(void)
{
	printf("Move Player  : [UP (W) | DOWN (S) | LEFT (A) | RIGHT (D)]\n");
	printf("Rotate View  : [ARROW LEFT | ARROW RIGHT]\n");
    printf("Dimension ±  : [R]");
	printf("Exit         : [ESC]\n");
}

bool _valid_map(char *path) {
    return true;
}

bool	guard(int ac, char **av)
{
    if (ac == 2 && _valid_map(av[1]))
        return (true);

    printf("Invalid number of arguments!!\n");
    printf("Uses: ./cub3D [PATH TO MAP]\n");
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

void *exit_fractal(void *obj) {
    return (NULL);
}

int	main(int argc, char **argv)
{
    t_window win;

    if (!guard(argc, argv))
        return (1);

    if (!initialization())
        return (printf("ERROR: Failed to initialize program!\n"));

    // mlx_hook(win.win, CROSS, 0, &exit_fractal, NULL);
    // mlx_key_hook(win.win, &key_hooks, NULL);
    // mlx_mouse_hook(win.win, &mouse_hooks, NULL);
    print_menu();
    // mlx_loop(win.mlx);
	return (0);
}