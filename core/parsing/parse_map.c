
#include "../../includes/main.h"

bool	is_line_empty(char *line);
bool	check_borders(char **map, int i, int j);
bool	is_valid_map_char(char c);
bool	is_valid_player_char(char c);

/*
	@brief Checks if the character is a valid player character
	@param c The character to check
	@return true if the character is a valid player character, false otherwise
*/
static bool	handle_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (!is_valid_map_char(map[i][j]))
			{
				printf("Invalid map char: %c\n", map[i][j]);
				ft_fprintf(STDERR_FILENO, "Error: Invalid map.\n");
				return (false);
			}
			if (map[i][j] != '1' && map[i][j] != ' ' &&
				!check_borders(map, i, j))
			{
				ft_fprintf(STDERR_FILENO, "Error: Invalid map.\n");
				return (false);
			}
			j++;
		}
	}
	return (true);
}

/*
	@brief Validates the player in the map
	@param str The string to validate
	@return true if the player is valid, false otherwise
*/
static bool	validate_player(char *str)
{
	bool	found;

	found = false;
	while (*str)
	{
		if (is_valid_player_char(*str))
		{
			if (found)
				return (false);
			found = true;
		}
		str++;
	}
	return (found);
}

/*
	@brief Reads the map from the file descriptor
	@param fd The file descriptor to read the map from
	@return The map read from the file descriptor
*/
static char	*read_map(int fd)
{
	char	*line;
	char	*text;
	char	*temp;
	bool	found;

	found = false;
	text = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		if (*line == '\n' && found)
		{
			free(line);
			free(text);
			return (NULL);
		}
		if (*line != '\n')
			found = true;
		temp = ft_strjoin(text, line);
		free(text);
		free(line);
		text = temp;
		line = get_next_line(fd);
	}
	return (text);
}

/*
	@brief Parses the map from the file descriptor
	@param map_fd The file descriptor to read the map from
	@param map The map to store the parsed map
	@return true if the map was parsed successfully, false otherwise

*/
bool	parse_map(int map_fd, t_map **map)
{
	char	*map_line;

	map_line = read_map(map_fd);
	if (!map_line)
		return (false);
	if (!validate_player(map_line))
	{
		free(map_line);
		return (false);
	}
	(*map)->map = ft_split(map_line, '\n');
	free(map_line);
	if (!(*map)->map)
		return (false);
	// ! FIXME: REMOVE THIS
	printf(GREEN BOLD"Map: \n"RESET_COLOR);
	for (int i = 0; (*map)->map[i]; i++)
	{
		for (int j = 0; (*map)->map[i][j]; j++) {
			if ((*map)->map[i][j] != '1' && (*map)->map[i][j] != '0')
				printf(RED UNDERLINE"%c"RESET_COLOR, (*map)->map[i][j]);
			else
				printf("%c", (*map)->map[i][j]);
		}
		printf("\n");
	}
	if (!handle_map((*map)->map))
		return (false);
	return (true);
}
