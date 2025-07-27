/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:15:46 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/27 19:02:02 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stddef.h>
#include <stdlib.h>

// char	**envdup(char **env, char *var)
// {
// 	int		len;
// 	int		index;
// 	char	**ret;
//
// 	len = 0;
// 	index = 0;
// 	while (env[len])
// 		len++;
// 	if (var)
// 		len++;
// 	ret = malloc((len + 1) * sizeof(char *));
// 	if (!ret)
// 		return (NULL);
// 	while (env[index])
// 	{
// 		ret[index] = ft_strdup(env[index]);
// 		index++;
// 	}
// 	if (var)
// 	{
// 		ret[index] = ft_strdup(var);
// 		index++;
// 	}
// 	ret[index] = NULL;
// 	return (ret);
// }

t_export	*new_node(char *name, char *value)
{
	t_export	*ret;

	ret = malloc(sizeof(t_export));
	if (!ret)
		return (NULL);
	ret->name = ft_strdup(name);
	ret->value = ft_strdup(value);
	ret->next = NULL;
	return (ret);
}

void	add_one_node(t_export *new, t_export **head)
{
	t_export *tmp;

	tmp = NULL;
	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		tmp = (*head);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	**splitenv(char *env)
{
	int		i;
	int		j;
	char	**ret;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char *) * 3);
	if (!ret)
		return (NULL);
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] == '\0')
		ret[1] = NULL;
	else if (env[i + 1] == '\0')
		ret[1] = ft_strdup("");
	else
	{
		while (env[i + j])
			j++;
		ret[1] = ft_substr(env, i + 1, j);
	}
	ret[0] = ft_substr(env, 0, i);
	ret[2] = NULL;
	return (ret);
}

int	arr_to_list(t_export **head, char **env)
{
	int		index;
	char	**tmp;

	index = 0;
	tmp = NULL;
	if (!head)
		return (TECHNICAL_ERR);
	while (env[index])
	{
		tmp = splitenv(env[index]);
		add_one_node(new_node(tmp[0], tmp[1]), head);
		index++;
	}
	free_array(tmp);
	return (SUCCES);
}

static size_t	list_size(t_export *export)
{
	size_t	ret;

	ret = 0;
	while (export)
	{
		ret++;
		export = export->next;
	}
	return (ret);
}

char	**env_to_arr(t_export *export)
{
	char	**ret;
	size_t	len;
	int		index;

	index = 0;
	len = list_size(export);
	ret = malloc((len + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (export)
	{
		if (export->name && !export->value)
			ret[index] = ft_strdup(export->name);
		else if (export->name && export->value[0] == '\0')
			ret[index] = ft_strjoin(export->name, "=");
		else
			ret[index] = ft_strjoin(ft_strjoin(export->name, "=")
						   , export->value);
		index++;
		export = export->next;
	}
	ret[index] = NULL;
	return (ret);
}
