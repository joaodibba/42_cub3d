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
	**map = (t_map){ .map = NULL, .floor = NULL, .ceiling = NULL, .no = NULL, .so = NULL, .we = NULL, .ea = NULL };
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

void paint_window(t_window *win, int color)
{
    int x;
    int y;

    // Paint the top half with the given color
	y = 0;
    while (y < WIN_HEIGHT / 2)
    {
        x = 0;
        while (x < WIN_WIDTH)
            put_pixel(win->img, x++, y, 0x00FF0000);  // Red color in hex
        y++;
    }
    y = WIN_HEIGHT / 2;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
            put_pixel(win->img, x++, y, color);
        y++;
    }

    // Paint the bottom half with red
}


int render(t_cub *cub)
{
	paint_window(cub->win, 0x0000ff00); //red
    render_2d_map(cub->map, cub->win);
	render_player(cub->map, cub->win);
    mlx_put_image_to_window(cub->win->mlx, cub->win->win, cub->win->img->img, 0, 0);
    return (0);
}


int main(int argc, char **argv)
{
    t_window        *win = NULL;
    t_map           *map = NULL;
    t_controller    ctrl;
    t_cub           *cub;

    if (!guard(argc, argv) || !initialization(&win, &map) || !parser(argv[1], &win, &map))
        return (2);
    ctrl = init_controller(win);
    print_menu();
    cub = (t_cub *)malloc(sizeof(t_cub));
    if (!cub)
    {
        ft_fprintf(STDERR_FILENO, "Error: Failed to allocate memory for cub.\n");
        return (2);
    }
    cub->win = win;
    cub->map = map;
    cub->ctrl = ctrl;

    mlx_loop_hook(win->mlx, &render, cub);
    mlx_loop(win->mlx);

    ft_free_array(map->map);
    free(map);
    free(win);
    free(cub);
    return (0);
}

