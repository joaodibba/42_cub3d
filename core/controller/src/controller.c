#include "../inc/controller.h"

static int key_press(int key, t_controller *ctrl) 
{
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

static int key_release(int key, t_controller *ctrl) 
{
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

static int mouse_move(int x, int y, t_controller *ctrl) 
{
    (void)y;  // Unused parameter
    if (x > 2 * (WIN_WIDTH / 3))
    {
        ctrl->rt_rt = true;
        ctrl->rt_lf = false;
    }
    else if (x < WIN_WIDTH / 3)
    {
        ctrl->rt_lf = true;
        ctrl->rt_rt = false;
    }
    else
    {
        ctrl->rt_rt = false;
        ctrl->rt_lf = false;
    }
    return (0);
}

int exit_cub(t_window *win) 
{
    ft_fprintf(STDOUT_FILENO, "You exited Cub3D\n");
    mlx_destroy_window(win->mlx, win->win);
    exit(0);
}

t_controller init_controller(t_window **win)
{
	t_controller ctrl;

    ctrl = (t_controller){ .mv_fw = false, .mv_bw = false, .mv_lf = false, .mv_rt = false, .rt_lf = false, .rt_rt = false, .game_over = false };
    mlx_hook((*win)->win, 2, (1L << 0), &key_press, &ctrl);
    mlx_hook((*win)->win, 3, (1L << 1), &key_release, &ctrl);
    mlx_hook((*win)->win, 17, (1L << 0), &exit_cub, *win);
    mlx_hook((*win)->win, 6, (1L << 6), &mouse_move, &ctrl);
}
