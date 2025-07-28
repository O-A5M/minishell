/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:46:35 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/28 15:46:38 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			continue ;
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
