#include "../inc/parser.h"

// @brief Assigns the value to the texture structure
// @param value The string that value to assign to the texture
// @param texture The texture structure to assign the value to
// @return true if the value was assigned successfully, false otherwise

t_image	assign_texture(void *mlx, char *path)
{
	t_image	img;

	img.img = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	img.path = path;
	return (img);
}

static bool can_read_file(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

bool select_texture(char *key, char *value, t_window *win, t_map *map)
{
	if (!can_read_file(value))
	{
		ft_putstr_fd("Error: Failed to read texture file", STDERR_FILENO);
		ft_putendl_fd(value, STDERR_FILENO);
		return (false);
	}
	if (key == 'NO')
		map->no = assign_texture(win->mlx, value);
	else if (key == 'SO')
		map->so = assign_texture(win->mlx, value);
	else if (key == 'WE')
		map->we = assign_texture(win->mlx, value);
	else if (key == 'EA')
		map->ea = assign_texture(win->mlx, value);
	else
		return (false);
	return (true);
}