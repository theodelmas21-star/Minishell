NAME = minishell
CC = cc
MY_SOURCES = main.c

MY_OBJECTS = $(MY_SOURCES:.c=.o) 
CFLAGS = -Wall -Wextra -Werror -g3

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

$(NAME): $(MY_OBJECTS)
	$(CC) $(CFLAGS) $(MY_OBJECTS) -lreadline -o $(NAME)

clean:
	rm -f $(MY_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re