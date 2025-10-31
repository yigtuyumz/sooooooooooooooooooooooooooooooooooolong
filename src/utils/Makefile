CC	:= cc
CFLAGS	:= -Wall -Wextra -Werror
AR	:= ar
ARFLAGS := rcs
SRC	:= utils.c
OBJ	:= $(SRC:.c=.o)
NAME	:= utils.a

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
