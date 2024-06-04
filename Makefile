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

# Compiler and Flags
CC      = cc
CFLAGS	= -g -fsanitize=address  #-Wall -Wextra -Werror

# Source directories and files
LFT = libft
MLX = mlx_linux

DIRS =	core \
		core/model \
		core/view \
		core/controller \
		dimension-2d \
		dimension-3d \
		entities \
		raycasting

SRC = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJ  = $(SRC:.c=.o)

# MLX Library Configuration
MLX_FLAGS = -L./$(MLX) -lmlx_Linux -L/usr/lib  -I$(MLX) -lXext -lX11 -lm -lz
ifeq ($(OS), Darwin)
	MLX = mlx_macos
	MLX_FLAGS = -L./$(MLX) -lmlx -framework OpenGL -framework AppKit
endif

# Include directories
INCLUDES = $(foreach dir, $(DIRS), $(wildcard $(dir)/inc))
INC = $(addprefix -I, $(INCLUDES))

# Main Build Rule
all: $(CUB)

$(CUB): $(OBJ)
	@printf "$(BL)Compiling $(LFT)$(RC)\n"
	@make -sC $(LFT) > /dev/null
	@printf "$(BL)Compiling $(MLX)$(RC)\n"
#	> /dev/null
	@make -sC $(MLX) 2> /dev/null
	@printf "$(BL)Compiling $(CUB)$(RC)\n"
	@$(CC) $(CFLAGS) -I$(MLX) $(INC) $^ -o $@ $(LFT)/libft.a $(MLX_FLAGS)
	@printf  "$(GR)$(CUB) Compiled!$(RC)\n"

%.o: %.c
	@printf "$(BL)Compiling $< into $@$(RC)\n"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ 

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

v: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(CUB) # Map argument still needed