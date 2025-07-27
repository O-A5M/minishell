#include "../minishell.h"
#include <unistd.h>

int	ft_echo(t_cmd *cmd)
{
	int	index;
	int	nl;

	index = 1;
	nl = 0;
	if (!cmd->args_array[1])
	{
		write(1, "\n", 1);
		return (SUCCES);
	}
	while (!ft_strncmp(cmd->args_array[index], "-n", 2))
	{
		index++;
		nl = 1;
	}
	while (cmd->args_array[index])
	{
		printf("%s", cmd->args_array[index]);
		if (cmd->args_array[index + 1] != NULL)
			printf(" ");
		index++;
	}
	if (nl == 0)
		printf("\n");
	return (SUCCES);
}
