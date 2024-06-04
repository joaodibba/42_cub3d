#include "../inc/parser.h"

/*
	@brief Checks if the key is a texture
	@param key The key to check
	@return true if the key is a texture, false otherwise
*/
static bool	is_texture(char *key)
{
	return (!ft_strncmp(key, "NO", 3) || !ft_strncmp(key, "SO", 3)
		|| !ft_strncmp(key, "WE", 3) || !ft_strncmp(key, "EA", 3));
}

/*
	@brief Checks if the key is a color
	@param key The key to check
	@return true if the key is a color, false otherwise
*/
static bool is_color(char *key)
{
	return (!ft_strncmp(key, "F", 2) || !ft_strncmp(key, "C", 2));
}

/*
	@brief Checks if all the configurations are set
	@param map The map structure
	@return true if all the configurations are set, false otherwise
*/
static bool all_configs_set(t_map *map)
{
	if (!map->floor || !map->ceiling || \
		!map->no || !map->so || \
		!map->ea || !map->we)
		return (false);
	return (true);
}

/*
	@brief Parses the line and assigns the value to the key in the map structure
	@param line The line to parse
	@param win The window structure
	@param map The map structure
	@return true if the line was parsed successfully, false otherwise
*/
static bool	parse_line(char *line, t_window **win, t_map **map)
{
	char	**key_value;
	char	*key;
	char	*value;

	key_value = ft_split(line, '\n');
	key_value = ft_split(*key_value, ' ');
	if (!key_value)
		return (false);
	if (ft_array_len(key_value) != 2)
	{
		ft_free_array(key_value);
		return (false);
	}
	key = *key_value;
	value = *(key_value + 1);
	if (is_texture(key) && !select_texture(key, value, win, map))
	{
		ft_free_array(key_value);
		return (false);
	}
	else if (is_color(key) && !select_color(key[0], value, map))
	{
		ft_free_array(key_value);
		return (false);
	}
	else if (!is_texture(key) && !is_color(key))
	{
		ft_fprintf(STDERR_FILENO, "Error: Found unexpected line: %s\n", line);
		ft_fprintf(STDERR_FILENO, "Hint: The cause of this might be a configuration missing, please check the map file\n");
		ft_free_array(key_value);
		return (false);
	}
	ft_free_array(key_value);
	return (true);
}

static void remove_nl(char **line)
{
	int i = 0;
	if (!*line)
		return;
	while ((*line)[i])
	{
		if ((*line)[i] == '\n')
		{
			(*line)[i] = '\0';
			break;
		}
		i++;
	}
}

bool get_line(int fd, char **line)
{
	*line = get_next_line(fd);
	if (!*line)
		return (false);
	remove_nl(line);
	return (true);
}

bool	is_line_empty(char *line)
{
	while (line && *line)
	{
		if (!is_space((unsigned char)*line))
			return (false);
		line++;
	}
	return (true);
}

bool	parse_configs(int map_fd, t_window **win, t_map **map)
{
	char	*line;

	while (get_line(map_fd, &line) == true && !all_configs_set(*map))
	{
		if (!line)
			break;
		printf("line: %s\n", line);
		if (is_line_empty(line))
			continue;
		if (!parse_line(line, win, map))
		{
			ft_fprintf(STDERR_FILENO, "Error: Failed to parse line: %s\n", line);
			ft_fprintf(STDERR_FILENO, "Error: Missing configurations\n");
			free(line);
			return (false);
		}
		free(line);
	}
	return (true);
}
