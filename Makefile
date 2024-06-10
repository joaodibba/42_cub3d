# Colors
RD      = \033[0;31m
GR      = \033[0;32m
YL      = \033[0;33m
BL      = \033[0;34m
MG      = \033[0;35m
PR      = \033[0;35m
CY      = \033[0;36m
RC      = \033[0m

# OS Detection
OS := $(shell uname)

# Project Name
CUB = cub3D

WIN_WIDTH = 1920
WIN_HEIGHT = 1080
SQUARE_SIZE = 16

# Compiler and Flags
CC      = 	cc
CFLAGS	=	-g \
			-DWIN_WIDTH=$(WIN_WIDTH) \
			-DWIN_HEIGHT=$(WIN_HEIGHT) \
			-DSQUARE_SIZE=$(SQUARE_SIZE) \
			-Wall -Wextra -Werror \
			-fsanitize=address

# Source directories and files
LFT = libft
MLX = mlx_linux

SRC	 =	core/view/mlx_helper.c \
		core/controller/controller.c \
		core/parsing/parse_configs.c \
		core/parsing/parse_configs_colors.c \
		core/parsing/parse_configs_textures.c \
		core/parsing/parse_configs_utils.c \
		core/parsing/parse_map.c \
		core/parsing/parse_map_utils.c \
		core/parsing/parser.c \
		dimension-2d/render.c \
		dimension-3d/render.c \
		entities/player.c \
		entities/player_movement.c \
		raycasting/helpers.c \
		raycasting/loggers.c \
		raycasting/raycast.c

OBJ  = $(SRC:.c=.o)

# MLX Library Configuration
MLX_FLAGS = -L./$(MLX) -lmlx_Linux -L/usr/lib  -I$(MLX) -lXext -lX11 -lm -lz

ifeq ($(OS), Darwin)
	MLX = mlx_macos
	MLX_FLAGS = -L./$(MLX) -lmlx -framework OpenGL -framework AppKit
endif

# Main Build Rule
all: $(CUB)

$(CUB): $(OBJ)
	@printf "$(BL)Compiling $(LFT)$(RC)\n"
	@make -sC $(LFT) > /dev/null
	@printf "$(BL)Compiling $(MLX)$(RC)\n"
	@make -sC $(MLX) 2> /dev/null
	@printf "$(BL)Compiling $(CUB)$(RC)\n"
	@$(CC) $(CFLAGS) -I$(MLX) $^ -o $@ $(LFT)/libft.a $(MLX_FLAGS)
	@printf  "$(GR) $(CUB) Compiled!$(RC)\n"

%.o: %.c
	@printf "$(BL)Compiling $< into $@$(RC)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(BL)Cleaning .o files$(RC)\n"
	@rm -f $(OBJ)
	@printf "$(BL)Cleaning $(LFT)$(RC)\n"
	@make clean -sC $(LFT) > /dev/null
	@printf "$(BL)Cleaning $(MLX)$(RC)\n"
	@make clean -sC $(MLX) > /dev/null

fclean: clean
	@printf "$(BL)Cleaning $(CUB)$(RC)\n"
	@rm -f $(CUB)
	@make fclean -sC $(LFT) > /dev/null

re: fclean all

bonus: all