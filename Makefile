# Minishell variables

CC = cc
CFLAGS = -Wall -Wextra -Werror
MINISHELL_SRC_FILES = minishell.c
MINISHELL_OBJ_FILES = $(MINISHELL_SRC_FILES:.c=.o)
UTILS_SRC_FILES = utils.c
UTILS_OBJ_FILES = $(UTLIS_SRC_FILES:.c=.o)
NAME = minishell

# Rules

all: $(NAME)

$(NAME): $(MINISHELL_OBJ_FILES) $(UTILS_OBJ_FILES)
	$(CC) $(CFLAGS) $(MINISHELL_OBJ_FILES) $(UTILS_OBJ_FILES) -o $(NAME)

clean:
	rm -f $(MINISHELL_OBJ_FILES) $(UTILS_OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

# Extra rules

.PHONY: clean
.SECONDARY: $(MINISHELL_OBJ_FILES) $(UTILS_OBJ_FILES)
