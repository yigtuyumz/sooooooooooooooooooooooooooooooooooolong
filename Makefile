# The := operator creates static (simply expanded) variables.
# Their values are evaluated only once, not recalculated each time they are used.
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
NAME			:= solong

MLX_DIR			:= minilibx-linux
MLX_LIB			:= $(MLX_DIR)/libmlx.a
MLX_FLAGS		:= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

LOGGER_DIR		:= src/logger
LOGGER_LIB		:= $(LOGGER_DIR)/logger.a

SRC_DIR			:= src
OBJ_DIR			:= obj
SRC_FILES		:= main.c
SRC				:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ				:= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

INCLUDES		:= -I$(MLX_DIR) -I$(LOGGER_DIR)
LIBS			:= $(MLX_LIB) $(LOGGER_LIB)

all: $(NAME)

$(NAME): $(LIBS) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LOGGER_LIB) -o $(NAME)

# Order only prerequisites only impose a "must exist beforehand"
# They do not trigger a rebuild based on timestamps
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LOGGER_LIB):
	$(MAKE) -C $(LOGGER_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LOGGER_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LOGGER_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

