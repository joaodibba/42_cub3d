#ifndef PARSER_H
# define PARSER_H


# include "model.h"

# ifndef TEXTURE_WIDTH
#  define TEXTURE_WIDTH 128
# endif

# ifndef TEXTURE_HEIGHT
#  define TEXTURE_HEIGHT 128
# endif

#include "main.h"


bool	parser(char *path, t_window **win, t_map **map);

#endif