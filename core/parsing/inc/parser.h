#ifndef __PARSER_H__
# define __PARSER_H__

# if defined(__APPLE__)
#  include "../../mlx_macos/mlx.h"
# else
#  include "../../mlx_linux/mlx.h"
# endif

# include "../../../libft/libft.h"
# include "../../cub/inc/cub.h"
# include "../../model/inc/model.h"
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

# ifndef TEXTURE_WIDTH
#  define TEXTURE_WIDTH 128
# endif

# ifndef TEXTURE_HEIGHT
#  define TEXTURE_HEIGHT 128
# endif

bool	parser(char *path, t_window **win, t_map **map);
bool	can_read_file(char *path);

bool	parse_configs(int map_fd, t_window **win, t_map **map);

bool	select_texture(char *key, char *value, t_window **win, t_map **map);

bool	select_color(char key, char *value, t_map **map);

bool	parse_map(int map_fd, char ***map);

bool	check_borders(char **map, int i, int j);
bool	is_valid_player_char(char c);
bool	is_valid_map_char(char c);
bool	is_space(char c);
bool	is_line_empty(char *line);

bool	get_line(int fd, char **line);

#endif