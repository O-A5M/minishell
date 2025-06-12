#include "minishell.h"

int	parser(char *cl)
{
	t_cmd			*command;
	t_args			*args;
	unsigned int	index;

	command = NULL;
	args = NULL;
	index = 0;
	while (cl[index])
	{
		while (is_a_whitespace(cl[index]))
			index += 1;
		if (is_other(cl[index]))
			other_found(cl, &index, &args, &command);
		if (is_a_quote(cl[index]))
			quote_found(cl, &index, &args, &command);
		if (is_an_expansion(cl[index]))
			expansion_found(cl, &index, &args, &command);
		if (is_a_pipe(cl[index]))
			pipe_found(cl, &index, &args, &command);
		if (is_a_redir(cl[index]))
			redir_found(cl, &index, &args, &command);
	}
}
