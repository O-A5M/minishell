CC = cc
CFLAGS = -g -Wall -Wextra -Werror

# Minishell variables

MINISHELL_SRC_FILES = minishell.c signal.c parser.c\
					  exit_1.c exit_2.c expansion_token.c\
					  argument_triggered.c other_token.c\
					  quoted_token.c struct_functions_1.c\
					  struct_functions_2.c struct_functions_3.c\
					  token_type_functions_1.c token_type_functions_2.c\
					  free.c redirection_token_0.c redirection_token_1.c\
					  execution/source/execution.c\
					  execution/source/execution_utils.c\
					  environment/set_env.c execution/source/pipe_line.c\
					  execution/source/handle_built_ins.c built-in/cd.c\
					  built-in/echo.c built-in/pwd.c built-in/env.c\
					  built-in/export.c built-in/unset.c built-in/exit.c\
					  execution/source/child_ctrl_utils.c\
					  environment/set_env_utils.c manage_env_list.c\
					  redirection_token_2.c redirection_token_3.c\
					  execution/source/other_utils.c\
					  execution/source/pipe_line_utils.c get_functions_0.c\
					  get_functions_1.c execution/source/redir_utils.c

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
