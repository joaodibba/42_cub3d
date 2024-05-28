
#include "../inc/parser.h"

void	replace_spaces(char *line)
{
	int	size;

	if (!line)
		return ;
	size = ft_strlen(line);
	while (--size >= 0 && is_space(line[size]))
		line[size] = '\31';
}

static char	*skip_empty_lines(int map_fd)
{
	char	*line;

	while (get_line(map_fd, line) == true)
	{
		if (!is_line_empty(line))
			break ;
		free(line);
	}
	replace_spaces(line);
	return (line);
}

static bool	handle_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != ' ' && !check_borders(map, i, j))
				return (false);
			j++;
		}
	}
	return (true);
}

bool validate_player(char *str) 
{
	bool found;
	
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

static char *read_map(int map_fd)
{
	char *long_line;
	char *line;
	char *tmp;
	char *text;

	long_line = skip_empty_lines(map_fd);
	if (!long_line)
		return (NULL);
	text = long_line;
	while (get_line(map_fd, line) == true)
	{
		tmp = ft_strjoin(text, line);
		free(text);
		free(line);
		text = tmp;
	}
	return (text);
}

bool parse_map(char ***map, int map_fd)
{
	char *map_line;

	map_line = read_map(map_fd);
	if (!map_line)
		return (false);
	if (!validate_player(map_line))
	{
		free(map_line);
		return (false);
	}
	*map = ft_split(map_line, '\31');
	free(map_line);
	if (!map)
		return (false);
	if (!handle_map(*map))
	{
		ft_free_array(*map);
		free(map);
		return (false);
	}
	return (true);
}
