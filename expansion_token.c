/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:36:14 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/07/25 19:31:32 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*expand_token(char *cl, unsigned int *index, char **env)
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
		expanded_token = ft_itoa(return_status);
	}
	else
		expanded_token = ft_strdup("$");
	return (expanded_token);
}
