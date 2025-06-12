#include "minishell.h"

char	**list_to_array(t_args **args)
{
	char	**arr;
	t_args	*ptr;
	size_t	len;
	int		index;

	len = args_amount(args);
	arr = malloc(sizeof(char *) * (len + 1));
	if (arr = NULL)
		return (NULL);
	ptr = *args;
	index = 0;
	while (ptr != NULL)
	{
		arr[index] = ptr->arg;
		index += 1;
		ptr = ptr->next;
	}
	arr[index] = NULL;
	return (arr);
}

void	add_to_last_command(t_cmd **command, char **arr)
{
	t_cmd	*ptr;

	ptr = *command;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->args = arr;
}

void	pipe_found(t_cmd **command, t_args **args)
{
	char	**arr;

	arr = list_to_array(args);
	add_to_last_command(command, arr);
	append_command(command, NULL);
	free_args(args);
}
