#include "../includes/main.h"

void	_check_for_colision(t_player *player, char **map, t_vec_double dir)
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
	if (map[(int)(player->pos.y)][(int)(player->pos.x + dir.x
			+ collision.x)] == '0')
		player->pos.x += dir.x;
	if (map[(int)(player->pos.y + dir.y
			+ collision.y)][(int)(player->pos.x)] == '0')
		player->pos.y += dir.y;
}

void	rotate_vector(t_vec_double *vec, double angle)
{
	double			rad;
	t_vec_double	tmp;

	rad = angle * M_PI / 180;
	tmp = (t_vec_double){.x = vec->x, .y = vec->y};
	vec->x = tmp.x * cos(rad) - tmp.y * sin(rad);
	vec->y = tmp.x * sin(rad) + tmp.y * cos(rad);
}

void	rotate_player_dir(t_vec_double *vector, t_vec_double *rotate)
{
	double			theta;
	t_vec_double	tmp;

	theta = atan2(rotate->y, rotate->x) + M_PI / 2;
	tmp = (t_vec_double){.x = vector->x, .y = vector->y};
	vector->x = tmp.x * cos(theta) + tmp.y * -sin(theta);
	vector->y = -tmp.x * -sin(theta) + tmp.y * cos(theta);
}

void	_normalizer(t_vec_double *vector)
{
	double	length;

	length = sqrt((vector->x * vector->x) + (vector->y * vector->y));
	vector->x /= length;
	vector->y /= length;
}

void	player_move(t_player *player, t_controller *controller, char **map)
{
	t_vec_double	move_dir;

	move_dir = (t_vec_double){0, 0};
	move_dir.y -= (controller->mv_fw);
	move_dir.y += (controller->mv_bw);
	move_dir.x -= (controller->mv_lf);
	move_dir.x += (controller->mv_rt);
	if (controller->rt_lf)
		rotate_vector(&player->dir, -ROT_SPEED);
	if (controller->rt_rt)
		rotate_vector(&player->dir, ROT_SPEED);
	if (move_dir.x == 0 && move_dir.y == 0)
		return ;
	rotate_player_dir(&move_dir, &player->dir);
	move_dir.x *= MOVE_SPEED;
	move_dir.y *= MOVE_SPEED;
	_check_for_colision(player, map, move_dir);
	_normalizer(&player->dir);
}
