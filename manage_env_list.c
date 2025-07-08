/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:15:37 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/08 18:37:26 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_path(t_export *export)
{
	char		**ret;
	t_export	*tmp;

	tmp = export;
	while (tmp)
	{
		if (!ft_strncmp("PATH", tmp->name, 4))
		{
			ret = ft_split(tmp->value, ':');
			// if (!ret)
				//exit_status; TODO
			return (ret);
		}
		tmp = tmp->next;
	}
	free_env(&export);
	return (NULL);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

t_export	*ft_new_node(char *s, char *str)
{
	t_export	*ret;

	ret = malloc(sizeof(t_export));
	if (!ret)
		return (NULL);
	ret->name = s;
	ret->value = str;
	ret->next = NULL;
	return (ret);
}

void	add_last(t_export **s, t_export *t)
{
	t_export	*tmp;

	if (!s || !t)
		return ;
	if (!*s)
	{
		(*s) = t;
	}
	else
	{
		tmp = *s;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = t;
	}
}

t_export	*split_env(char **env)
{
	t_export	*ret;
	char		**splits;
	int		i;

	i = 0;
	ret = NULL;
	while (env[i])
	{
		splits = ft_split(env[i], '=');
		add_last(&ret, ft_new_node(splits[0], splits[1]));
		i++;
	}
	free_array(splits);
	return (ret);
}
