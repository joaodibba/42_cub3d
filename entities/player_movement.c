#include "../includes/main.h"

void	move_if_valid(t_player *player, char **map, t_vec_double dir)
{
	t_vec_double	collision;

	collision = (t_vec_double){0, 0};
	if (dir.x > 0)
		collision.x = 0.1;
	else if (dir.x < 0)
		collision.x = -0.1;
	if (dir.y > 0)
		collision.y = 0.1;
	else if (dir.y < 0)
		collision.y = -0.1;
	if (map[(int)(player->pos.y)][(int)(player->pos.x + dir.x + collision.x)] \
		&& map[(int)(player->pos.y)][(int)(player->pos.x + dir.x + collision.x)] == '0')
		player->pos.x += dir.x;
	if (map[(int)(player->pos.y + dir.y + collision.y)][(int)(player->pos.x)] \
		&& map[(int)(player->pos.y + dir.y + collision.y)][(int)(player->pos.x)] == '0')
		player->pos.y += dir.y;
}

void	rotate_vector_by_angle(t_vec_double *vector, double angle)
{
	double	new_x;
	double	new_y;

	new_x = vector->x * cos(angle) - vector->y * sin(angle);
	new_y = vector->x * sin(angle) + vector->y * cos(angle);
	*vector = (t_vec_double) {new_x, new_y};
}

void	normalize_vector_dbl(t_vec_double *vector)
{
	double	gcd;

	gcd = sqrt(vector->x * vector->x + vector->y * vector->y);
	if (gcd != 0)
		*vector = (t_vec_double){vector->x / gcd, vector->y / gcd};
	else
		*vector = (t_vec_double){0, 0};
}

double	degree_to_radian(double degree)
{
	return (degree * M_PI / 180);
}

void	player_move(t_player *player, t_controller *controller, char **map)
{
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
		move_dir = (t_vec_double){move_dir.x * MOVE_SPEED, move_dir.y * MOVE_SPEED};
		move_if_valid(player, map, move_dir);
	}
}