/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:15:46 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/22 18:32:56 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_export	*set_env(char **env)
{
	t_export	*ret;
	char		**split_env;
	int			index;

	index = 0;
	while(env[index])
	{
		split_env = ft_split(env[index], '=');
		if (!split_env)
			return (NULL);
		add_last(&ret, ft_new_node(split_env[0], split_env[1]));
		index++;
	}
	free_array(split_env);
	return (ret);
}

void	free_env(t_export **export)
{
	t_export	*tmp;

	while (*export)
	{
		tmp = (*export)->next;
		free (tmp->name);
		free (tmp->value);
		free (*export);
		*export = tmp;
	}
}

char	**envdup(char **env, char *var)
{
	int		len;
	char	**ret;

	len = 0;
	while (env[len])
		len++;
	if (var)
		len++;
	ret = malloc((len + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	len = 0;
	while (env[len])
	{
		ret[len] = ft_strdup(env[len]);
		len++;
	}
	if (var)
	{
		ret[len] = ft_strdup(var);
		len++;
	}
	ret[len] = NULL;
	return (ret);
}
