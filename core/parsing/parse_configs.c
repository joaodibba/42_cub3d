/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:02:30 by jalves-c          #+#    #+#             */
/*   Updated: 2024/06/10 21:02:32 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

bool	is_line_empty(char *line);
bool	all_configs_set(t_map *map);
bool	gnl(int fd, char **line);
bool	parse_line(char *line, t_window *win, t_map *map);

/*
	@brief Parses the configurations from the map file
	@param map_fd The file descriptor of the map file
	@param win The window structure
	@param map The map structure
	@return true if the configurations were parsed successfully, false otherwise
*/
bool	parse_configs(int map_fd, t_window *win, t_map *map)
{
	char	*line;

	while (!all_configs_set(map) && gnl(map_fd, &line) == true)
	{
		if (!line)
			break ;
		if (is_line_empty(line))
		{
			free(line);
			continue ;
		}
		if (!parse_line(line, win, map))
		{
			ft_fprintf(STDERR_FILENO, "Error: Failed to parse line: %s\n", \
					line);
			ft_fprintf(STDERR_FILENO, "Error: Missing configurations\n");
			free(line);
			return (false);
		}
		free(line);
	}
	return (true);
}
