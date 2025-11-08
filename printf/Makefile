CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libftfprintf.a

FT_SRCS = ft_fprintf.c
FT_OBJS = $(FT_SRCS:.c=.o)

.SUFFIXES:
.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(FT_OBJS)
	ar rcs $(NAME) $(FT_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(FT_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
