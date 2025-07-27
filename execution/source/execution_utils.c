/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:07:13 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/25 18:20:15 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_command(char **path, char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (path[i])
	{
		str = ft_strjoin(path[i], s);
		if (access(str, X_OK) == 0)
		{
			free (str);
			return (i);
		}
		free (str);
		i++;
	}
	return (-1);
}

char	*search_command(t_cmd *cmd, char **path)
{
	char	*ret;
	int		index;
	char	*tmp;

	ret = NULL;
	tmp = NULL;
	index = -1;
	if (!cmd->args_array[0])
		return (NULL);
	if (ft_strchr(cmd->args_array[0], '/'))
	{
		if (access(cmd->args_array[0], X_OK) == 0)
			return (ft_strdup(cmd->args_array[0]));
	}
	else
	{
		tmp = ft_strjoin("/", cmd->args_array[0]);
		while (path[++index])
		{
			ret = ft_strjoin(path[index], tmp);
			if (access(ret, X_OK) == 0)
				return (ret);
		}
	}
	free (ret);
	free (tmp);
	return (NULL);
}
