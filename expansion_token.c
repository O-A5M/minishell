/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:36:14 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/06/13 12:36:15 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_split(char *expanded, char *ifs, int *index, t_cmd **cmd_head)
{
	char	*ret;
	char	*ifs;
	// int		flag;

	ifs = " \t\n";
	// flag = 0;
	if (is_in_ifs(expanded[*index], ifs))
		(*cmd_head)->last_node->args_list->arg_is_done = 1;
	while (expanded[*index] && is_in_ifs(expanded[*index], ifs))
		*index += 1;
	if (expanded[*index])
	{
		while (expanded[*index] && !is_in_ifs(expanded[*index], ifs))
			*index += 1;
		;
	}
	;
	return (ret);
}

int	field_split(char *expanded, char *ifs, t_cmd **cmd_head, int done_arg)
{
	char	*arg;
	int		i;

	if (!expanded[0])
	{
		free(expanded);
		if ((*cmd_head)->last_node->args_list->arg_is_done == 0)
			(*cmd_head)->last_node->args_list->arg_is_done == done_arg;
		return (0);
	}
	i = 0;
	while (expanded[i] && is_in_ifs(expanded[i], ifs))
		i++;
	if (!expanded[i])
	{
		free(expanded);
		(*cmd_head)->last_node->args_list->arg_is_done == 1;
		return (0);
	}
	i = 0;
	arg = my_split(expanded, ifs, &i, cmd_head);
	while (arg)
	{
		append_arg(&(((*cmd_head)->last_node)->args_list), arg, 0);
		arg = my_split(expanded, ifs, &i, cmd_head);
	}
}

char	*valid_token_expansion(char *cl, unsigned int *index)
{
	char			*variable_name;
	char			*expanded_variable;
	unsigned int	start_index;

	start_index = *index;
	while (cl[*index] == '_' || ft_isalnum(cl[*index]))
		*index += 1;
	variable_name = ft_substr(cl, start_index, *index - start_index);
	expanded_variable = ft_strdup(getenv(variable_name));
	free(variable_name);
	if (expanded_variable == NULL)
		expanded_variable = ft_strdup("");
	return (expanded_variable);
}

char	*get_expanded_token(char *cl, unsigned int *index)
{
	char			*expanded_token;

	*index += 1;
	if (cl[*index] == '_' || ft_isalpha(cl[*index]))
		expanded_token = valid_token_expansion(cl, index);
	else if (is_a_quote(cl[*index]))
		expanded_token = ft_strdup("");
	else if (cl[*index] == '?')
	{
		*index += 1;
		expanded_token = ft_itoa(EXIT_FAILURE);
	}
	else
		expanded_token = ft_strdup("$");
	return (expanded_token);
}
