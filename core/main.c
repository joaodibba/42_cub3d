#include "../includes/main.h"
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
	printf("bpp: %d\n", (*win)->img->bpp);
	printf("line_len: %d\n", (*win)->img->line_len);
	printf("endian: %d\n", (*win)->img->endian);
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

static void	render_player(t_map *map, t_window *win, t_controller ctrl)
{
	t_vec_double	pos = (t_vec_double){ .x = 2, .y = 2 };
	t_vec_double	dir = (t_vec_double){ .x = 1, .y = 0 };
	t_vec_double	plane = (t_vec_double){ .x = 0, .y = 0.66 };
	t_player		player = (t_player){ .pos = pos, .dir = dir, .plane = plane };
	t_computes		computes;

	mlx_put_image_to_window(win->mlx, win->win, win->img->img, 0, 0);
}

int render(t_cub *cub)
{
	render_2d_map(cub->map, cub->win);
	render_player(cub->map, cub->win, cub->ctrl);
	mlx_put_image_to_window(cub->win->mlx, cub->win->win, cub->win->img->img, 0, 0);
	return (0);
}

#define MAP_WIDTH  16
#define MAP_HEIGHT 7
#include <string.h>
void	init_temp_map(t_map *map)
{
    // Allocate memory for the map
    map->map = (char **)malloc(MAP_HEIGHT * sizeof(char *));
    if (!map->map)
    {
        ft_fprintf(STDERR_FILENO, "Error: Failed to allocate memory for map.\n");
        return;
    }
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        map->map[i] = (char *)malloc((MAP_WIDTH + 1) * sizeof(char));
        if (!map->map[i])
        {
            ft_fprintf(STDERR_FILENO, "Error: Failed to allocate memory for map row %d.\n", i);
            ft_free_array(map->map);
            return;
        }
    }
    char _map[MAP_HEIGHT][MAP_WIDTH + 1] = {
        "111111111",
        "100000001",
        "10N111001",
        "100101001",
        "100111001",
        "100000001",
        "111111111"
    };
    for (int i = 0; i < MAP_HEIGHT; i++) {
       strcpy(map->map[i], _map[i]);
	}
    map->width = MAP_WIDTH;
    map->height = MAP_HEIGHT;
}


int main(int argc, char **argv)
{
	t_window		*win = NULL;
	t_map			*map = NULL;
	t_controller	ctrl;
	t_cub			cub;

	if (!guard(argc, argv) || !initialization(&win, &map))
		return (2);
	ctrl = init_controller(win);
	init_temp_map(map);
	print_menu();
	cub = (t_cub){ .win = win, .map = map, .ctrl = ctrl };

	mlx_loop_hook(win->mlx, &render, &cub);
	mlx_loop(win->mlx);

	ft_free_array(map->map);
	free(map);
	free(win);
	return (0);
}
