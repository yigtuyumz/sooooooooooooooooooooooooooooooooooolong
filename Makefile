CC          := cc
CFLAGS      := -Wall -Wextra -Werror
NAME        := solong

# MiniLibX
MLX_DIR     := minilibx-linux
MLX_LIB     := $(MLX_DIR)/libmlx.a
MLX_FLAGS   := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Source & Object files
SRC_DIR     := src
OBJ_DIR     := obj
SRC_FILES   := main.c
SRC         := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ         := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

# Link final binary only if needed
$(NAME): $(OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

# Compile .c → .o only when source or headers change
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

# Create obj directory only once
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build MiniLibX only if not already built or changed
$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

