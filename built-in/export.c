#include "../minishell.h"

int	ft_export(t_cmd *cmd, char **env)
{
	int		index;
	char	**tmp;

	index = 1;
	tmp = NULL;
	if (!cmd->args_array[1])
	{
		index = 0;
		while (env[index])
		{
			printf("declare -x %s\n", env[index]);
			index++;
		}
		return (SUCCES);
	}
	else
	{
		while (cmd->args_array[index])
		{
			tmp = env;
			env = envdup(tmp, cmd->args_array[index]);
			free (tmp);
			index++;
		}
	}
	return (SUCCES);
}
