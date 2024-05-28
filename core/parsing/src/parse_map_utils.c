
#include "../inc/parser.h"

bool check_borders(char **map, int i, int j)
{
	if (j == 0 || i == 0 || !map[i + 1] || !map[i - 1] || !map[i][j + 1] || !map[i][j - 1])
		return (false);
	if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ' || map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
		return (false);
	return (true);
}


bool	is_valid_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');

}

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == '\n');
}

bool is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

bool	is_line_empty(char *line)
{
	while (*line)
	{
		if (!is_space(*line))
			return (false);
		line++;
	}
	return (true);
}