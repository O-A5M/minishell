/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:15:46 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/28 15:50:24 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	t_export	*tmp;

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

void	copy_to_env(t_export *export, char ***ret, int index)
{
	char	*tmp;

	tmp = NULL;
	if (export->name && !export->value)
		(*ret)[index] = ft_strdup(export->name);
	else if (export->name && export->value[0] == '\0')
		(*ret)[index] = ft_strjoin(export->name, "=");
	else
	{
		tmp = ft_strjoin(export->name, "=");
		(*ret)[index] = ft_strjoin(tmp, export->value);
		free(tmp);
	}
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
		copy_to_env(export, &ret, index);
		index++;
		export = export->next;
	}
	ret[index] = NULL;
	return (ret);
}
