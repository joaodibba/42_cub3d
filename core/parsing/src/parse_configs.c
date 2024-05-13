#include "../inc/parser.h"

// @brief Checks if the key is a texture
// @param key The key to check
// @return true if the key is a texture, false otherwise
static bool	is_texture(char *key)
{
	return (!ft_strcmp(key, "NO") || !ft_strcmp(key, "SO")
		|| !ft_strcmp(key, "WE") || !ft_strcmp(key, "EA"));
}

// @brief Checks if the key is a color
// @param key The key to check
// @return true if the key is a color, false otherwise
static bool is_color(char *key)
{
	return (!ft_strcmp(key, "F") || !ft_strcmp(key, "C"));
}

static bool	parse_line(char *line, t_window *win, t_map *map)
{
	char	**key_value;
	char	*key;
	char	*value;

	key_value = ft_split(line, ' ');
	if (!key_value)
		return (false);
	if (ft_array_len(key_value) != 2)
	{
		ft_putendl_fd("Error: Invalid line format", STDERR_FILENO);
		ft_free_array(key_value);
		return (false);
	}
	key = *key_value;
	value = *(key_value + 1);
	if (is_texture(key) && !assign_texture(win->mlx, value))
	{
			ft_putendl_fd("Error: Failed to assign texture", STDERR_FILENO);
			ft_free_array(key_value);
			return (false);

	}
	else if (is_color(key) && !select_color(key[0], value, &map))
	{
			ft_putendl_fd("Error: Failed to assign color", STDERR_FILENO);
			ft_free_array(key_value);
			return (false);

	}
	else if (!is_texture(key) && !is_color(key))
	{
		ft_putendl_fd("Error: Invalid key", STDERR_FILENO);
		ft_free_array(key_value);
		return (false);
	}
	ft_free_array(key_value);
	return (true);
}

static bool get_line(int fd, char *line)
{
	line = get_next_line(fd);
	if (!line)
		return (false);
	return (true);

}

bool	parse_configs(int map_fd, t_window *win, t_map *map)
{
	// Read the file line by line
	// assigns the value to the key in the map structure
	// if the key is a color, it will convert the value to an integer
	// if the key is a texture, it will assign the value to the texture path in the map structure

	char	*line;

	while (get_line(map_fd, &line) == true)
	{
		if (!parse_line(line, win, map))
		{
			free(line);
			return (false);
		}
		free(line);
	}
	return (true);
}