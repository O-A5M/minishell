CC = cc
CFLAGS = -g -Wall -Wextra -Werror

# Minishell variables

MINISHELL_SRC_FILES = minishell.c signal.c parser.c exit_1.c exit_2.c expansion_token.c argument_triggered.c other_token.c quoted_token.c struct_functions_1.c struct_functions_2.c struct_functions_3.c token_type_functions_1.c token_type_functions_2.c free.c
MINISHELL_OBJ_FILES = $(MINISHELL_SRC_FILES:.c=.o)
NAME = minishell

# Libft variables

LIBFT_D = libft
LIBFT_N = libft/libft.a

# Rules

all: $(NAME)

$(NAME): $(MINISHELL_OBJ_FILES) $(LIBFT_N)
	$(CC) $(CFLAGS) $(MINISHELL_OBJ_FILES) $(LIBFT_N) -lreadline -o $(NAME)

$(LIBFT_N):
	$(MAKE) -C $(LIBFT_D)

clean:
	rm -f $(MINISHELL_OBJ_FILES)
	$(MAKE) clean -C $(LIBFT_D)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_D)

re: fclean $(NAME)

# Extra rules

.PHONY: clean
.SECONDARY: $(MINISHELL_OBJ_FILES) $(LIBFT_N)
