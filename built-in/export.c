#include "../minishell.h"
#include <unistd.h>

static void	print_env(char *env)
{
	int	i;

	i = 0;
	write(1, "declare -x ", 11);
	while (env[i])
	{
		write(1, &env[i], 1);
		if (env[i] == '=')
			write(1, "\"", 1);
		i++;
	}
	if (ft_strchr(env, '='))
		write(1, "\"", 1);
	write (1, "\n", 1);
}

static int	check_for_dup(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], name, strlen(name)))
			return (i);
		i++;
	}
	return (-1);
}

static int	change_elements(char *name, char ***env)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_split(name, '=');
	if ((i = check_for_dup(tmp[0], *env)) == -1)
	{
		free_array(tmp);
		return (-1);
	}
	free ((*env)[i]);
	(*env)[i] = NULL;
	(*env)[i] = ft_strdup(name);
	free_array(tmp);
	return (SUCCES);
}

int	ft_export(t_cmd *cmd, char ***env)
{
	int		index;
	char	**tmp;

	index = 1;
	tmp = NULL;
	if (!cmd->args_array[1])
	{
		index = 0;
		while ((*env)[index])
		{
			print_env((*env)[index]);
			index++;
		}
		return (SUCCES);
	}
	else
	{
		while (cmd->args_array[index])
		{
			if (SUCCES == change_elements(cmd->args_array[index], env))
				index++;
			else
			{
				tmp = *env;
				*env = envdup(tmp, cmd->args_array[index]);
				free_array(tmp);
				index++;
			}
		}
	}
	return (SUCCES);
}
