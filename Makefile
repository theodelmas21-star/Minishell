NAME = minishell
CC = cc
MY_SOURCES = src/main.c \
	src/signals.c \
	src/lexer/lexer.c \
	src/lexer/lexer_states.c \
	src/lexer/handle_states.c \
	src/lexer/utils/lexer_utils.c \
	src/lexer/utils/create_token.c \
	src/utils/utils_free.c \
	src/utils/utils_check_char.c \
	src/parser/parser.c \
	src/exec/exec.c \
	src/exec/exec_prep.c \
	src/exec/paths.c \
	src/exec/redirs/redirs.c \
	src/exec/redirs/redirs_utils.c \
	src/exec/utils_exec.c \
	src/utils/ft_strjoin_free.c \
	src/built-in/env.c \
	src/built-in/echo.c \
	src/built-in/export/export.c \
	src/built-in/pwd.c \
	src/built-in/export/export_utils.c \
	src/built-in/export/export_options.c \
	src/built-in/export/export_continue.c \
	src/built-in/handle_builtins.c \
	src/built-in/unset.c \
	src/built-in/cd.c \
	src/built-in/exit.c \
	src/expander/expander.c \
	src/expander/expand_env.c \
	src/expander/expand_hd.c \
	src/expander/expand_new.c \
	src/expander/expand_continue.c \
	src/built-in/export/local_variable.c \

MY_OBJECTS = $(MY_SOURCES:.c=.o) 
CFLAGS = -Wall -Wextra -Werror -g3

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a


all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(MY_OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(MY_OBJECTS) $(LIBFT) -lreadline -o $(NAME)

clean:
	rm -f $(MY_OBJECTS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re