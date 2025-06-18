#include "minishell.h"

int	parser(char *cl)
{
	t_cmd			*command;
	// t_args			*args;
	unsigned int	index;
	int				i;

	command = create_command(NULL, NULL, NULL);
	// args = NULL;
	index = 0;
	while (cl[index])
	{
		while (is_a_whitespace(cl[index]))
			index += 1;
		if (is_other(cl[index]))
			other_found(cl, &index, &command);
		if (is_a_quote(cl[index]))
			quote_found(cl, &index, &command);
		if (is_an_expansion(cl[index]))
			expansion_found(cl, &index, &command);
		if (is_a_pipe(cl[index]))
			pipe_found(cl, &index, &command);
		if (is_a_redir(cl[index]))
			redir_found(cl, &index, &command);
	}
	while (command != NULL)
	{
		// print all the args here

		i = 0;
		while (command->args_array[i] != NULL)
		{
			printf("%s\n", command->args_array[i]);
			i += 1;
		}
		printf("\n");
		while (command->redirections != NULL)
		{
			printf("redir type: %d, to file: %s\n",
					command->redirections->redir_type,
					command->redirections->filename);
			command->redirections = command->redirections->next;
		}
		command = command->next;
	}
}
