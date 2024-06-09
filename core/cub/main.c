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
	**map = (t_map){ .map = NULL, .floor = 0, .ceiling = 0, .no = NULL, .so = NULL, .we = NULL, .ea = NULL };
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

void	render_dimension_3d(t_cub *cub)
{
	unsigned int	i;

	i = -1;
	while (++i < WIN_WIDTH)
		raycast(i, cub->map, &cub->player, &cub->cols[i]);
	create_wall(cub->win->img, cub->cols, cub->map, &cub->player);
}

void paint_window(t_window *win, int ceiling_color, int floor_color)
{
    int x;
    int y;

    // Paint the top half with the given color
	y = 0;
    while (y < WIN_HEIGHT / 2)
    {
        x = 0;
        while (x < WIN_WIDTH)
            put_pixel(win->img, x++, y, ceiling_color);
        y++;
    }
    y = WIN_HEIGHT / 2;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
            put_pixel(win->img, x++, y, floor_color);
        y++;
    }
}
void move_if_valid(t_player *player, char **map, t_vec_double dir) {
    t_vec_double collision;

    collision.x = 0;
    collision.y = 0;
    if (dir.x > 0)
        collision.x = 0.1;
    else if (dir.x < 0)
        collision.x = -0.1;
    if (dir.y > 0)
        collision.y = 0.1;
    else if (dir.y < 0)
        collision.y = -0.1;
    if ( map[(int)(player->pos.y)][(int)(player->pos.x + dir.x + collision.x)] && map[(int)(player->pos.y)][(int)(player->pos.x + dir.x + collision.x)] == '0')
        player->pos.x += dir.x;
    if (map[(int)(player->pos.y + dir.y + collision.y)][(int)(player->pos.x)] && map[(int)(player->pos.y + dir.y + collision.y)][(int)(player->pos.x)] == '0')
        player->pos.y += dir.y;
}

void rotate_vector_by_angle(t_vec_double *vector, double angle) {
    double new_x = vector->x * cos(angle) - vector->y * sin(angle);
    double new_y = vector->x * sin(angle) + vector->y * cos(angle);
    vector->x = new_x;
    vector->y = new_y;
}

void normalize_vector_dbl(t_vec_double *vector) {
    double gcd;

    gcd = sqrt(vector->x * vector->x + vector->y * vector->y);
    if (gcd != 0) {
        vector->x /= gcd;
        vector->y /= gcd;
    } else {
        vector->x = 0;
        vector->y = 0;
    }
}

double degree_to_radian(double degree)
{
	return (degree * M_PI / 180);
}

void player_move(t_player *player, t_controller *controller, char **map) {
    t_vec_double move_dir = {0, 0};

    if (controller->mv_fw)
        move_dir.y -= 1;
    if (controller->mv_bw)
        move_dir.y += 1;
    if (controller->mv_lf)
        move_dir.x -= 1;
    if (controller->mv_rt)
        move_dir.x += 1;

    if (controller->rt_lf == true)
		rotate_vector_by_angle(&player->dir, degree_to_radian(-2));
	if (controller->rt_rt == true)
    	rotate_vector_by_angle(&player->dir, degree_to_radian(2));


    if (move_dir.x != 0 || move_dir.y != 0)
	{
        normalize_vector_dbl(&move_dir);
        rotate_vector_by_angle(&move_dir, atan2(player->dir.y, player->dir.x));
        move_dir.x *= MOVE_SPEED;
        move_dir.y *= MOVE_SPEED;
        move_if_valid(player, map, move_dir);
    }
}

int cube_loop(t_cub *cub)
{
	player_move(&cub->player, cub->ctrl, cub->map->map);
	paint_window(cub->win, cub->map->ceiling, cub->map->floor);
	// render_dimension_3d(cub);
	render_2d_map(cub->map, cub->win, cub->player);
	mlx_put_image_to_window(cub->win->mlx, cub->win->win, cub->win->img->img, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
    t_window        *win = NULL;
    t_map           *map = NULL;
    t_controller    *ctrl = NULL;
    t_cub           *cub;

    if (!guard(argc, argv) || !initialization(&win, &map) || !parser(argv[1], &win, &map))
        return (2);
    ctrl = init_controller(win);
    cub = (t_cub *)malloc(sizeof(t_cub));
    if (!cub)
    {
        ft_fprintf(STDERR_FILENO, "Error: Failed to allocate memory for cub.\n");
        return (2);
    }
    ctrl = init_controller(win);
	if (!ctrl)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to initialize controller.\n");
		return (2);
	}
    cub->win = win;
    cub->map = map;
    cub->ctrl = ctrl;
	init_player(&cub->player, map);

	print_menu();
    mlx_loop_hook(win->mlx, &cube_loop, cub);
    mlx_loop(win->mlx);

    ft_free_array(map->map);
    free(map);
    free(win);
    free(cub);
    return (0);
}

