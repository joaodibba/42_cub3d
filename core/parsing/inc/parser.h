#ifndef __PARSER_H__
# define __PARSER_H__

#if defined(__APPLE__)
	#include "../mlx_macos/mlx.h"
#else
	#include "../mlx_linux/mlx.h"
#endif

#include "../../cub/inc/cub.h"
#include "../../../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <errno.h>

// @brief Parse the map from the file descriptor
// @param path The path to the map file
// @param map The map structure to store the parsed map
// @param win The window structure to store textures
// @return true if the map was parsed successfully, false otherwise
bool	parser(char *path, t_window *win, t_map *map);

// @brief Parse the configs from the file
// @param map_fd The file descriptor of the map file
// @param map The map structure to store the parsed map
bool	parse_configs(int map_fd, t_window *win ,t_map *map);

// @brief Parse the map from the file descriptor
// @param map_fd The file descriptor of the map file
// @param map The map double array to store the parsed map
// @return true if the map was parsed successfully, false otherwise
bool parse_map(int map_fd, char ***map);

#endif