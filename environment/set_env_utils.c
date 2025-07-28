/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:48:10 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/28 15:50:14 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		free_array(tmp);
		index++;
	}
	return (SUCCES);
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

void	free_export_list(t_export *head)
{
	t_export	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = tmp;
	}
}
