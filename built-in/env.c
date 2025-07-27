#include "../minishell.h"

int	ft_env(char **env)
{
	int	index;

	index = 0;
	while (env[index])
	{
		if (ft_strchr(env[index], '='))
			printf("%s\n", env[index]);
		index++;
	}
	return (SUCCES);
}
