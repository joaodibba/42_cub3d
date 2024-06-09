#include "../../includes/main.h"

bool	can_read_file(char *path);

/*
	@brief Assigns the value to the texture structure
	@param value The string that value to assign to the texture
	@param texture The texture structure to assign the value to
	@return true if the value was assigned successfully, false otherwise
*/
t_image	*assign_texture(void *mlx, char *path)
{
	t_image	*img;

	if (!can_read_file(path))
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to read texture file:'%s'\n",
				path);
		return (NULL);
	}
	img = (t_image *)malloc(sizeof(t_image));
	if (!img)
	{
		ft_fprintf(STDERR_FILENO,
				"Error: Failed to allocate memory for texture.\n");
		return (NULL);
	}
	img->img = mlx_xpm_file_to_image(mlx, path, &(img->width), &(img->height));
	if (img->width > TEXTURE_SIZE || img->height > TEXTURE_SIZE)
	{
		ft_fprintf(STDERR_FILENO,
				"Error: '%s' image width and height should be %d", path, TEXTURE_SIZE);
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &(img->bpp), &(img->line_len),
			&(img->endian));
	img->path = ft_strdup(path);
	return (img);
}

bool	select_texture(char *key, char *value, t_window *win, t_map *map)
{
	if (!map || !win)
	{
		ft_fprintf(STDERR_FILENO, "Error: Invalid map or window structure\n");
		return (false);
	}
	if (!can_read_file(value))
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to read texture file: %s\n", \
		value);
		return (false);
	}
	if (!ft_strncmp(key, "NO", 3) && !map->no)
	{
		map->no = assign_texture(win->mlx, value);
		if (!map->no)
			return (false);
	}
	else if (!ft_strncmp(key, "SO", 3) && !map->so)
	{
		map->so = assign_texture(win->mlx, value);
		if (!map->so)
			return (false);
	}
	else if (!ft_strncmp(key, "WE", 3) && !map->we)
	{
		map->we = assign_texture(win->mlx, value);
		if (!map->we)
			return (false);
	}
	else if (!ft_strncmp(key, "EA", 3) && !map->ea)
	{
		map->ea = assign_texture(win->mlx, value);
		if (!map->ea)
			return (false);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to assign texture\n");
		return (false);
	}
	return (true);
}
