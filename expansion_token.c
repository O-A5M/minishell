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

char	*my_split(char *expanded, char *ifs, int *index, t_cmd **cmd_head)
{
	char			*ret;
	unsigned int	start;
	size_t			len;

	ret = NULL;
	if (is_in_ifs(expanded[*index], ifs) && (*cmd_head)->last_node->args_list)
		(*cmd_head)->last_node->args_list->arg_is_done = 1;
	while (expanded[*index] && is_in_ifs(expanded[*index], ifs))
		*index += 1;
	if (expanded[*index])
	{
		start = (unsigned int)*index;
		while (expanded[*index] && !is_in_ifs(expanded[*index], ifs))
			*index += 1;
		len = (size_t)((unsigned int)*index - start);
		ret = ft_substr(expanded, start, len);
		if (!ret)
			return (NULL);
		return (ret);
	}
	return (ret);
}

int	field_split(char *expanded, char *ifs, t_cmd **cmd_head, int done_arg)
{
	char	*arg;
	int		i;
	int		ret;

	i = 0;
	while (expanded[i] && is_in_ifs(expanded[i], ifs))
		i++;
	if (!expanded[i])
	{
		(*cmd_head)->last_node->expansion_flag = 1;
		if ((*cmd_head)->last_node->args_list)
			(*cmd_head)->last_node->args_list->arg_is_done = 1;
		free(expanded);
		return (0);
	}
	i = 0;
	while ((arg = my_split(expanded, ifs, &i, cmd_head)))
		append_arg(&(((*cmd_head)->last_node)->args_list), arg, 0);
	if ((*cmd_head)->last_node->args_list &&
		(*cmd_head)->last_node->args_list->arg_is_done == 0)
		(*cmd_head)->last_node->args_list->arg_is_done = done_arg;
	ret = 0;
	if (expanded[i])
		ret = -1;
	free(expanded);
	return (ret);
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
