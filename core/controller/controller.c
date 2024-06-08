#include "../../includes/main.h"

static int	key_press(int key, t_controller *ctrl)
{
	if (key == UP || key == W)
		ctrl->mv_fw = true;
	if (key == DOWN || key == S)
		ctrl->mv_bw = true;
	if (key == LEFT || key == A)
		ctrl->mv_lf = true;
	if (key == RIGHT || key == D)
		ctrl->mv_rt = true;
	if (key == Q)
		ctrl->rt_lf = true;
	if (key == E)
		ctrl->rt_rt = true;
	return (0);
}

static int	key_release(int key, t_controller *ctrl)
{
	if (key == UP || key == W)
		ctrl->mv_fw = false;
	if (key == DOWN || key == S)
		ctrl->mv_bw = false;
	if (key == LEFT || key == A)
		ctrl->mv_lf = false;
	if (key == RIGHT || key == D)
		ctrl->mv_rt = false;
	if (key == Q)
		ctrl->rt_lf = false;
	if (key == E)
		ctrl->rt_rt = false;
	return (0);
}

static int	mouse_move(int x, int y, t_controller *ctrl)
{
	// (void)y; // Unused parameter rotation is only on the x axis
	// if (x > 2 * (WIN_WIDTH / 3))
	// {
	// 	ctrl->rt_rt = true;
	// 	ctrl->rt_lf = false;
	// }
	// else if (x < WIN_WIDTH / 3)
	// {
	// 	ctrl->rt_lf = true;
	// 	ctrl->rt_rt = false;
	// }
	// else
	// {
	// 	ctrl->rt_rt = false;
	// 	ctrl->rt_lf = false;
	// }
	return (0);
}

int	exit_cub(t_window *win)
{
	ft_fprintf(STDOUT_FILENO, "You exited Cub3D\n");
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
}

t_controller	*init_controller(t_window *win)
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
	mlx_hook(win->win, 2, (1L << 0), &key_press, ctrl);   // Key press event
	mlx_hook(win->win, 3, (1L << 1), &key_release, ctrl); // Key release event
	mlx_hook(win->win, 17, (1L << 0), &exit_cub, win);     // Close button event
	// mlx_hook(win->win, 6, (1L << 6), &mouse_move, ctrl);  // Mouse move event
	return (ctrl);
}