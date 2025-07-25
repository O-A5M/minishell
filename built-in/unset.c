#include "../minishell.h"

char	**remove_item(char **env, int index)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[j])
		j++;
	tmp = malloc((j + 1) * sizeof(char *));
	if (!tmp)
		return (NULL);
	j = 0;
	while (env[i])
	{
		if (i != index)
		{
			tmp[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

int	ft_unset(t_cmd *cmd, char ***env)
{
	int	i;
	int	j;
	char	**tmp;

	i = 1;
	tmp = NULL;
	while (cmd->args_array[i])
	{
		j = 0;
		while ((*env)[j])
		{
			if (ft_strnstr((*env)[j], cmd->args_array[i],
				  strlen(cmd->args_array[i])))
			{
				tmp = *env;
				*env = remove_item(tmp, j);
				free_array (tmp);
			}
			j++;
		}
		i++;
	}
	return (SUCCES);
}
