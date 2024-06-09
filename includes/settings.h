#ifndef SETTINGS_H
# define SETTINGS_H

#ifndef WIN_WIDTH
# define WIN_WIDTH 800
#endif

#ifndef WIN_HEIGHT
# define WIN_HEIGHT 600
#endif

#ifndef SQUARE_SIZE
# define SQUARE_SIZE 10
#endif

#ifndef PLAYER_SIZE
# define PLAYER_SIZE 2
#endif

// player macros
# define MOVE_SPEED 0.055

# ifdef __APPLE__
#  define ESC 53
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define Q 12
#  define E 14
#  define UP 126
#  define DOWN 125
#  define LEFT 123
#  define RIGHT 124
# endif

# ifdef __linux__
#  define ESC 65307
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define Q 113
#  define E 101
#  define UP 65362
#  define DOWN 65364
#  define LEFT 65361
#  define RIGHT 65363
# endif


#endif