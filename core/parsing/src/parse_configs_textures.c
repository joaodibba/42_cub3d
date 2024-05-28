#include "../inc/parser.h"

/*
	@brief Assigns the value to the texture structure
	@param value The string that value to assign to the texture
	@param texture The texture structure to assign the value to
	@return true if the value was assigned successfully, false otherwise
*/
t_image	*assign_texture(void *mlx, char *path)
{
	t_image	*img;

	img = (t_image *)malloc(sizeof(t_image));
	if (!img)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to allocate memory for texture.\n");
		return (NULL);
	}
	img->img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (img->width > TEXTURE_WIDTH || img->height > TEXTURE_HEIGHT)
	{
		ft_fprintf(STDERR_FILENO, "Error: '%s' image Width and Height should be %d and %d respectively.\n", path, TEXTURE_WIDTH, TEXTURE_HEIGHT);
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	img->path = path;
	return (img);
}

/*
	@brief Selects the texture based on the key
	@param key The key to select the texture
	@param value The value to assign to the texture
	@param win The window structure
	@param map The map structure
	@return true if the texture was assigned successfully, false otherwise
*/
bool select_texture(char *key, char *value, t_window *win, t_map *map)
{
	if (!can_read_file(value))
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to read texture file: %s\n", value);
		return (false);
	}
	if (!ft_strncmp(key, "NO", 3))
	{
		if (map->no)
		{
			ft_fprintf(STDERR_FILENO,"Error: 'NO' texture file path, specified more than once.\n");
			return (false);
		}
		map->no = assign_texture(win->mlx, value);
		if (!map->no)
			return (false);
	}
	else if (!ft_strncmp(key, "SO", 3))
	{
		if (map->so)
		{
			ft_fprintf(STDERR_FILENO, "Error: 'SO' texture file path, specified more than once.\n");
			return (false);
		}
		map->so = assign_texture(win->mlx, value);
		if (!map->so)
			return (false);
	}
	else if (!ft_strncmp(key, "WE", 3))
	{
		if (map->we)
		{
			ft_fprintf(STDERR_FILENO, "Error: 'WE' texture file path, specified more than once.\n");
			return (false);	
		}
		map->we = assign_texture(win->mlx, value);
		if (!map->we)
			return (false);
	}
	else if (!ft_strncmp(key, "EA", 3))
	{
		if (map->ea)
		{
			ft_fprintf(STDERR_FILENO, "Error: 'EA' texture file path, specified more than once.\n");
			return (false);	
		}
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
