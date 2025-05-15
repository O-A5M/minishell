# Minishell variables

CC = cc
CFLAGS = -Wall -Wextra -Werror
MINISHELL_SRC_FILES = minishell.c
MINISHELL_OBJ_FILES = $(MINISHELL_SRC_FILES:.c=.o)
NAME = minishell

# Libft variables

LIBFT_D = libft
LIBFT_N = $(LIBFT_D)/libft.a

# Rules

all: $(NAME)

$(NAME): $(MINISHELL_OBJ_FILES) $(UTILS_OBJ_FILES) $(LIBFT_D)
	$(CC) $(CFLAGS) $(MINISHELL_OBJ_FILES) $(LIBFT_D) -o $(NAME)

$(LIBFT_N):
	$(MAKE) -C $(LIBFT_D)

clean:
	rm -f $(MINISHELL_OBJ_FILES) $(UTILS_OBJ_FILES)
	clean -C $(LIBFT_D)

fclean: clean
	rm -f $(NAME)
	fclean -C $(LIBFT_D)

re: fclean $(NAME)

# Extra rules

.PHONY: clean
.SECONDARY: $(MINISHELL_OBJ_FILES) $(UTILS_OBJ_FILES)
