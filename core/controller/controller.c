#include "../../includes/main.h"

int	exit_cub(t_cub *cub)
{
	ft_fprintf(STDOUT_FILENO, "You exited Cub3D\n");
	mlx_destroy_window(cub->win->mlx, cub->win->win);
	exit(0);
}

static int	key_press(int key, t_cub *cub)
{
	if (key == UP || key == W)
		cub->ctrl->mv_fw = true;
	if (key == DOWN || key == S)
		cub->ctrl->mv_bw = true;
	if (key == LEFT || key == A)
		cub->ctrl->mv_lf = true;
	if (key == RIGHT || key == D)
		cub->ctrl->mv_rt = true;
	if (key == Q)
		cub->ctrl->rt_lf = true;
	if (key == E)
		cub->ctrl->rt_rt = true;
	if (key == ESC)
		exit_cub(cub);
	return (0);
}

static int	key_release(int key, t_cub *cub)
{
	if (key == UP || key == W)
		cub->ctrl->mv_fw = false;
	if (key == DOWN || key == S)
		cub->ctrl->mv_bw = false;
	if (key == LEFT || key == A)
		cub->ctrl->mv_lf = false;
	if (key == RIGHT || key == D)
		cub->ctrl->mv_rt = false;
	if (key == Q)
		cub->ctrl->rt_lf = false;
	if (key == E)
		cub->ctrl->rt_rt = false;
	return (0);
}

t_controller	*init_controller(t_cub *cub)
{
	t_controller	*ctrl;

	ctrl = (t_controller *)malloc(sizeof(t_controller));
	if (!ctrl)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to allocate memory for controller.\n");
		return (NULL);
	}
	*ctrl = (t_controller){.mv_fw = false, .mv_bw = false, .mv_lf = false,
		.mv_rt = false, .rt_lf = false, .rt_rt = false, .game_over = false};
	mlx_hook(cub->win->win, 2, (1L << 0), &key_press, cub);
	mlx_hook(cub->win->win, 3, (1L << 1), &key_release, cub);
	mlx_hook(cub->win->win, 17, 0L, &exit_cub, cub);
	return (ctrl);
}