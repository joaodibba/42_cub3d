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
CFLAGS	= #-Wall -Wextra -Werror

# Source directories and files
LFT = libft
MLX = mlx-linux
ifeq ($(OS), Darwin)
	MLX = mlx-mac
endif

DIRS = 2D 3D core/controller core/cub core/model core/view entities parsing raycasting textures $(LFT) $(MLX)
SRC = $(foreach dir, $(DIRS), $(wildcard $(dir)/src/*.c))
OBJ  = $(SRC:.c=.o)

# MLX Library Configuration
MLX_FLAGS = -L./$(MLX) -l$(MLX) -lXext -lX11 -lm -lz
ifeq ($(OS), Darwin)
	MLX_FLAGS = -L$(MLX) -l$(MLX) -framework OpenGL -framework AppKit
endif

# Include directories
INCLUDES = $(foreach dir, $(DIRS), $(wildcard $(dir)/inc))
INC = $(addprefix -I, $(INCLUDES))

# Main Build Rule
all: logs $(CUB)

logs:
	@mkdir -p logs && touch logs/cub3D.log

$(CUB): $(OBJ)
	@echo "$(GR)Compiling $(LFT)$(RC)"
	@make -sC $(LFT) > logs/cub3D.log
	@echo "$(GR)Compiling $(MLX)$(RC)"
#@make -sC $(MLX) 2>&1 > /logs/mlx.log
	@echo "$(GR)Compiling $(CUB)$(RC)"
	@$(CC) $(CFLAGS) $(INC) $^ -o $@ $(LFT)/libft.a $(MLX_FLAGS) > logs/cub3D.log

%.o: %.c
	@echo "$(GR)Compiling $< into $@$(RC)"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ > logs/cub3D.log

clean:
	@rm -f $(OBJ)

fclean: clean
	@echo "$(BL)Deleting $(CUB) and cleaning libft$(RC)"
	@rm -f $(CUB)
	@make fclean -sC $(LFT)

re: fclean all

bonus: all

v: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(CUB) # Map argument still needed
