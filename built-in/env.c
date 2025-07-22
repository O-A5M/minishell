#include "../minishell.h"

int	ft_env(char **env)
{
	int	index;

	index = 0;
	while (env[index])
	{
		printf("%s\n", env[index]);
		index++;
	}
	return (SUCCES);
}
