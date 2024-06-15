/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphuyal <rphuyal@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:48:54 by rphuyal           #+#    #+#             */
/*   Updated: 2024/06/15 15:49:47 by rphuyal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

void	print_menu(void)
{
	ft_printf("---------- CONTROLS ----------\n");
	ft_printf(GREEN BOLD "Movements:\n" RESET_COLOR);
	ft_printf("FORWARD     : [UP (W | ⬆)]\n");
	ft_printf("BACK        : [DOWN (S | ⬇)]\n");
	ft_printf("LEFT        : [LEFT (A)]\n");
	ft_printf("RIGHT       : [RIGHT (D)]\n\n");
	ft_printf(GREEN BOLD "Rotatations :\n" RESET_COLOR);
	ft_printf("LEFT        : [LEFT (Q | ⬅)]\n");
	ft_printf("RIGHT       : [RIGHT (E | →)]\n\n");
	ft_printf(GREEN BOLD "Others:\n" RESET_COLOR);
	ft_printf("Exit        : [CLOSE (ESC)]\n");
	ft_printf("------------------------------\n");
}

static bool	guard(int ac, char **av, t_cub *cub)
{
	if (ac == 2 && av[0] && av[1])
		return (true);
	free_cub(cub);
	ft_fprintf(STDERR_FILENO, "Error: Invalid use.\n");
	ft_fprintf(STDERR_FILENO, "Usage: ./cub3D [path/to/map.ber]\n");
	return (false);
}

void		update_camera_plane(t_player *player);
void		draw_line(t_image *img, t_vec_double *start, t_vec_double *line_len, int color);

int	cube_loop(t_cub *cub)
{
	player_move(&cub->player, cub->ctrl, cub->map->map);
	paint_window(cub->win, cub->map->ceiling, cub->map->floor);
	update_camera_plane(&cub->player);
	render_dimension_3d(cub);
	render_2d_map(cub, cub->map, cub->win, cub->player);
	mlx_put_image_to_window(cub->win->mlx, cub->win->win, cub->win->img->img, 0, 0);

	unsigned int count_down = cub->start - time(NULL);
	if (count_down > 0) {
		// still time left. put it on the screen
		char *elapsed = ft_itoa(count_down);
		mlx_string_put(cub->win->mlx, cub->win->win, WIN_WIDTH - 50, WIN_HEIGHT - 50, 0xFF0000, elapsed); // still not working
		free(elapsed);
	} else if (count_down <= 0) {
		// time ran out
		mlx_string_put(cub->win->mlx, cub->win->win, WIN_WIDTH - 100, WIN_HEIGHT - 50, 0xFF0000, "Game Over");
	}
	return (0);
}

void	null_cub_configs(t_cub *cub)
{
	cub->win = NULL;
	cub->map = NULL;
	cub->ctrl = NULL;
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = (t_cub *)malloc(sizeof(t_cub));
	null_cub_configs(cub);
	if (!cub)
	{
		ft_fprintf(STDERR_FILENO,
			"Error: Failed to allocate memory for cub.\n");
		return (2);
	}
	if (!guard(argc, argv, cub) || !initialization(cub) || !parser(cub, argv[1],
			cub->win, cub->map))
		return (2);
	cub->ctrl = init_controller(cub);
	if (!cub->ctrl)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to initialize controller.\n");
		exit_cub(cub);
		return (2);
	}
	init_player(&cub->player, cub->map);
	print_menu();
	cub->start = time(NULL) + 10;
	mlx_loop_hook(cub->win->mlx, &cube_loop, cub);
	mlx_loop(cub->win->mlx);
	return (0);
}
