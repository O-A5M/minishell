#include "../minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int	index;
	int	nl;

	index = 1;
	nl = 0;
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
