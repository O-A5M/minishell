/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:36:14 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/07/30 15:29:39 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_split(char *expanded, char *ifs, int *index, t_cmd **command)
{
	char			*ret;
	unsigned int	start;
	size_t			len;

	ret = NULL;
	if (is_in_ifs(expanded[*index], ifs) && (*command)->last_node->args_list)
		(*command)->last_node->args_list->last_node->arg_is_done = 1;
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

void	init_vars_and_loop(char *expanded, int *i, int *j, int *ret)
{
	*i = 0;
	*j = 0;
	*ret = 0;
	while (expanded[*i] && is_in_ifs(expanded[*i], " \t\n"))
		*i += 1;
	return ;
}

int	field_split(char *expanded, char *ifs, t_cmd **command, int done_arg)
{
	char	*arg;
	int		i;
	int		j;
	int		ret;

	init_vars_and_loop(expanded, &i, &j, &ret);
	if (!expanded[i] && (*command)->last_node->args_list)
		(*command)->last_node->args_list->last_node->arg_is_done = 1;
	else if (expanded[i])
	{
		arg = my_split(expanded, ifs, &j, command);
		while (arg != NULL)
		{
			append_arg(&(((*command)->last_node)->args_list), arg, 0);
			arg = my_split(expanded, ifs, &j, command);
		}
		if (expanded[j])
			ret = -1;
		if ((*command)->last_node->args_list && done_arg == 1)
			(*command)->last_node->args_list->last_node->arg_is_done = 1;
	}
	free(expanded);
	return (ret);
}

char	*valid_token_expansion(char *cl, unsigned int *index, char **env)
{
	char			*variable_name;
	char			*expanded_variable;
	unsigned int	start_index;

	start_index = *index;
	while (cl[*index] == '_' || ft_isalnum(cl[*index]))
		*index += 1;
	variable_name = ft_substr(cl, start_index, *index - start_index);
	expanded_variable = ft_strdup(ft_getenv(variable_name, env));
	free(variable_name);
	if (expanded_variable == NULL)
		expanded_variable = ft_strdup("");
	return (expanded_variable);
}

char	*get_expanded_token(char *cl, unsigned int *index, char **env)
{
	char			*expanded_token;

	*index += 1;
	if (cl[*index] == '_' || ft_isalpha(cl[*index]))
		expanded_token = valid_token_expansion(cl, index, env);
	else if (is_a_quote(cl[*index]))
		expanded_token = ft_strdup("");
	else if (cl[*index] == '?')
	{
		*index += 1;
		expanded_token = ft_itoa(g_return_status);
	}
	else
		expanded_token = ft_strdup("$");
	return (expanded_token);
}
