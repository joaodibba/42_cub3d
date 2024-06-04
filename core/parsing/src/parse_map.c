
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

	while (get_line(map_fd, &line) == true)
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
		while (map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] != '1' && map[i][j] != ' ' && !check_borders(map, i, j))
			{
				printf("Error: Invalid map.\n");
				printf("i: %d, j: %d\n", i, j);
				return (false);
			}
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

bool get_linha(int fd, char **line)
{
	*line = get_next_line(fd);
	if (!*line)
		return (false);
	return (true);
}

static char	*read_map(int fd)
{
	char	*line;
	char	*text;
	char	*temp;

	text = ft_strdup("");
	while (get_linha(fd, &line) == true)
	{
		temp = ft_strjoin(text, line);
		free(text);
		free(line);
		text = temp;
	}
	return (text);
}

bool parse_map(int map_fd, char **map)
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
	map = ft_split(map_line, '\31');
	printf("map: \n");
	for (int i = 0; map[i]; i++)
		printf("%s\n", map[i]);
	free(map_line);
	if (!map)
		return (false);
	if (!handle_map(map))
	{
		ft_free_array(map);
		return (false);
	}
	return (true);
}
