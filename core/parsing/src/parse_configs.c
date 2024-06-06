#include "../inc/parser.h"

bool	is_texture(char *key);
bool	is_color(char *key);
bool	is_line_empty(char *line);
bool	all_configs_set(t_map *map);
bool	gnl(int fd, char **line);
bool	select_texture(char *key, char *value, t_window **win, t_map **map);
bool	select_color(char key, char *value, t_map **map);

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

/*
	@brief Parses the configurations from the map file
	@param map_fd The file descriptor of the map file
	@param win The window structure
	@param map The map structure
	@return true if the configurations were parsed successfully, false otherwise
*/
bool	parse_configs(int map_fd, t_window **win, t_map **map)
{
	char	*line;

	while (!all_configs_set(*map) && gnl(map_fd, &line) == true)
	{
		if (!line)
			break ;
		if (is_line_empty(line))
			continue ;
		if (!parse_line(line, win, map))
		{
			ft_fprintf(STDERR_FILENO, "Error: Failed to parse line: %s\n",
					line);
			ft_fprintf(STDERR_FILENO, "Error: Missing configurations\n");
			free(line);
			return (false);
		}
		free(line);
	}
	return (true);
}
