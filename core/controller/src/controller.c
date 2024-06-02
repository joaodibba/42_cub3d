#include "../inc/controller.h"

int	key_press(int key, t_controller *ctrl) 
{
	if (key == ESC)
	{
		ctrl->game_over = true;
		ft_fprintf(STDOUT_FILENO, "Escape key was pressed\n");
	}
	if (key == UP || key == W)
	{
		ctrl->mv_fw = true;
		ft_fprintf(STDOUT_FILENO, "Up key was pressed\n");
	}
	if (key == DOWN || key == S)
	{
		ctrl->mv_bw = true;
		ft_fprintf(STDOUT_FILENO, "Down key was pressed\n");
	}
	if (key == LEFT || key == A)
	{
		ctrl->mv_lf = true;
		ft_fprintf(STDOUT_FILENO, "Left key was pressed\n");
	}
	if (key == RIGHT || key == D)
	{
		ctrl->mv_rt = true;
		ft_fprintf(STDOUT_FILENO, "Right key was pressed\n");
	}
	return (0);
}

int	key_release(int key, t_controller *ctrl) 
{
	if (key == ESC)
	{
		ctrl->game_over = false;
		ft_fprintf(STDOUT_FILENO, "Escape key was released\n");
	}
	if (key == UP || key == W)
	{
		ctrl->mv_fw = false;
		ft_fprintf(STDOUT_FILENO, "Up key was released\n");
	}
	if (key == DOWN || key == S)
	{
		ctrl->mv_bw = false;
		ft_fprintf(STDOUT_FILENO, "Down key was released\n");
	}
	if (key == LEFT || key == A)
	{
		ctrl->mv_lf = false;
		ft_fprintf(STDOUT_FILENO, "Left key was released\n");
	}
	if (key == RIGHT || key == D)
	{
		ctrl->mv_rt = false;
		ft_fprintf(STDOUT_FILENO, "Right key was released\n");
	}
    return (0);
}

int	mouse_move(int x, int y, t_controller *ctrl) 
{
	if (x > 2 * (WIN_WIDTH / 3))
		ctrl->rt_rt = true;
	else if ((x < WIN_WIDTH / 3))
		ctrl->rt_lf = true;
	else
	{
		ctrl->rt_rt = false;
		ctrl->rt_lf = false;
	}
    return (0);
}