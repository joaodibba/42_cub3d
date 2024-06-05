
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
				i = 0;
				printf("Error: Invalid map.\n");
				printf("i: %d, j: %d char: %c\n", i, j, map[i][j]);
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

// static char	*skip_empty_lines(int map_fd)
// {
// 	char	*line;

// 	while (get_linha(map_fd, &line) == true)
// 	{
// 		if (!is_line_empty(line))
// 			break ;
// 		free(line);
// 	}
// 	replace_spaces(line);
// 	return (line);
// }

static char	*read_map(int fd)
{
	char	*line;
	char	*text;
	char	*temp;

	text = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		temp = ft_strjoin(text, line);
		free(text);
		free(line);
		text = temp;
		line = get_next_line(fd);
	}
	return (text);
}

void remove_empty_lines_in_array(char ***array)
{
    int i = 0;

    while ((*array)[i])
    {
        if (!is_line_empty((*array)[i]))
            break;
        free((*array)[i]);
        int j = i;
        while ((*array)[j])
        {
            (*array)[j] = (*array)[j + 1];
            j++;
        }
    }
}

bool parse_map(int map_fd, char ***map)
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
	*map = ft_split(map_line, '\n');
	free(map_line);
	if (!*map)
		return (false);
	if (!handle_map(*map))
	{
		ft_free_array(*map);
		return (false);
	}
	return (true);
}
