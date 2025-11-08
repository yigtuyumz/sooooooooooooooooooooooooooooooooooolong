# The := operator creates static (simply expanded) variables.
# Their values are evaluated only once, not recalculated each time they are used.
CC				:=	cc
CFLAGS			:=	-Wall -Wextra -Werror
NAME			:=	solong

MLX_DIR			:=	minilibx-linux
MLX_LIB			:=	$(MLX_DIR)/libmlx.a
MLX_FLAGS		:=	-L$(MLX_DIR) -lmlx -lXext -lX11 -lm

UTILS_DIR		:=	src/utils
UTILS_SRC		:=	$(UTILS_DIR)/utils.c		\
					$(UTILS_DIR)/utils_date.c	\
					$(UTILS_DIR)/utils_memory.c
UTILS_LIB		:=	$(UTILS_DIR)/utils.a

FPRINTF_DIR	:=	printf
FPRINTF_SRC	:=	$(FPRINTF_DIR)/ft_fprintf.c
FPRINTF_LIB	:=	$(FPRINTF_DIR)/libftfprintf.a

SRC_DIR			:=	src
OBJ_DIR			:=	obj
SRC_FILES		:=	main.c		\
					app_alloc.c	\
					app_free.c
SRC				:=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ				:=	$(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

INCLUDES		:=	-I$(MLX_DIR) -I$(UTILS_DIR) -I$(FPRINTF_DIR)
LIBS			:=	$(MLX_LIB) $(LOGGER_LIB) $(UTILS_LIB) $(FPRINTF_LIB)

all: $(NAME)

$(NAME): $(LIBS) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(UTILS_LIB) $(FPRINTF_LIB) -o $(NAME)

# Order only prerequisites only impose a "must exist beforehand"
# They do not trigger a rebuild based on timestamps
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(FPRINTF_LIB): $(FPRINTF_SRC)
	$(MAKE) -C $(FPRINTF_DIR)

$(UTILS_LIB): $(UTILS_SRC)
	$(MAKE) -C $(UTILS_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(UTILS_DIR) clean
	$(MAKE) -C $(FPRINTF_DIR) clean


fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(UTILS_DIR) fclean
	$(MAKE) -C $(FPRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

