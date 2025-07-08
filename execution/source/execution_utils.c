/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:07:13 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/08 18:12:33 by oakhmouc         ###   ########.fr       */
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

void	free_env(t_export **export)
{
	t_export	*tmp;

	tmp = *export;
	while (tmp)
	{
		free (tmp->name);
		free (tmp->value);
		tmp = tmp->next;
	}
	free(*export);
}
