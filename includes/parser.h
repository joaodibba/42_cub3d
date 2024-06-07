#ifndef PARSER_H
# define PARSER_H


# include "model.h"

# ifndef TEXTURE_WIDTH
#  define TEXTURE_WIDTH 128
# endif

# ifndef TEXTURE_HEIGHT
#  define TEXTURE_HEIGHT 128
# endif


bool	parser(char *path, t_window **win, t_map **map);

bool	is_valid_player_char(char c);

bool	can_read_file(char *path);

#endif