#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

// static void	print_env(char *env)
// {
// 	int	i;
//
// 	i = 0;
// 	write(1, "declare -x ", 11);
// 	while (env[i])
// 	{
// 		write(1, &env[i], 1);
// 		if (env[i] == '=')
// 			write(1, "\"", 1);
// 		i++;
// 	}
// 	if (ft_strchr(env, '='))
// 		write(1, "\"", 1);
// 	write (1, "\n", 1);
// }
//
// char	**envdup2(char **env, char *var)
// {
// 	int		len;
// 	int		index;
// 	char	**ret;
//
// 	len = 0;
// 	index = 0;
// 	while (env[len])
// 		len++;
// 	ret = malloc((len + 2) * sizeof(char *));
// 	if (!ret)
// 		return (NULL);
// 	while (env[index])
// 	{
// 		ret[index] = ft_strdup(env[index]);
// 		index++;
// 	}
// 	ret[index++] = ft_strdup(var);
// 	ret[index] = NULL;
// 	return (ret);
// }
//
// static int	check_for_dup(char *name, char **env, int flag)
// {
// 	int	i;
//
// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strnstr(env[i], name, strlen(name))
// 			&& flag == 1)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }
//
// static int	change_elements(char *name, char ***env)
// {
// 	int		i;
// 	int		flag;
// 	char	**tmp;
//
// 	i = 0;
// 	flag = 0;
// 	if (ft_strchr(name, '='))
// 		flag = 1;
// 	tmp = ft_split(name, '=');
// 	if ((i = check_for_dup(tmp[0], *env, flag)) == -1)
// 	{
// 		free_array(tmp);
// 		if (flag == 0)
// 			return (-1);
// 		return (SUCCES);
// 	}
// 	free ((*env)[i]);
// 	(*env)[i] = ft_strdup(name);
// 	free_array(tmp);
// 	return (SUCCES);
// }
//
// int	ft_export(t_cmd *cmd, char ***env)
// {
// 	int		index;
// 	char	**tmp;
//
// 	index = 1;
// 	tmp = NULL;
// 	if (!cmd->args_array[1])
// 	{
// 		index = 0;
// 		while ((*env)[index])
// 		{
// 			print_env((*env)[index]);
// 			index++;
// 		}
// 		return (SUCCES);
// 	}
// 	else
// 	{
// 		while (cmd->args_array[index])
// 		{
// 			if (SUCCES == change_elements(cmd->args_array[index], env))
// 				index++;
// 			else
// 			{
// 				tmp = envdup(*env, NULL);
// 				free_array(*env);
// 				*env = envdup2(tmp, cmd->args_array[index]);
// 				free_array(tmp);
// 				index++;
// 			}
// 		}
// 	}
// 	return (SUCCES);
// }

void	print_env(t_export *export)
{
	while (export)
	{
		printf("declare -x ");
		if (export->value == NULL)
			printf("%s\n", export->name);
		else if (export->value[0] == '\0')
			printf("%s=\"\"\n", export->name);
		else
			printf("%s=\"%s\"\n", export->name, export->value);
		export = export->next;
	}
}

int	check_exist(char *cmd, t_export **export)
{
	char		**tmp;
	t_export	*tmp1;

	tmp = splitenv(cmd);
	tmp1 = (*export);
	while (tmp1)
	{
		if (!ft_strncmp(tmp[0], tmp1->name, ft_strlen(tmp[0]) + 1))
		{
			if (tmp[1] == NULL)
				return (SUCCES);
			tmp1->value = tmp[1];
			return (SUCCES);
		}
		tmp1 = tmp1->next;
	}
	return (-1);
}

int	is_valid(char *env, int *flag)
{
	int	i;

	i = 1;
	while (env[i])
	{
		if ((!ft_isalnum(env[i]) && env[i] != '_')
			|| (!ft_isalpha(env[i]) && env[0] != '_'))
		{
			if (*flag == 0)
			{
				ft_putstr_fd(env, 2);
				ft_putstr_fd(": Not a valid identifier\n", 2);
				*flag = 1;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export(t_cmd *cmd, t_export **export)
{
	int		index;
	char	**tmp;
	int		flag;

	index = 1;
	flag = 0;
	tmp = NULL;
	if (cmd->args_array[1] == NULL)
		return (print_env(*export), SUCCES);
	while (cmd->args_array[index])
	{
		if (check_exist(cmd->args_array[index], export) == SUCCES)
		{
			index++;
			continue;
		}
		tmp = splitenv(cmd->args_array[index]);
		if (!is_valid(tmp[0], &flag))
			add_one_node(new_node(tmp[0], tmp[1]), export);
		free_array(tmp);
		index++;
	}
	if (flag == 1)
		return (TECHNICAL_ERR);
	return (SUCCES);
}
