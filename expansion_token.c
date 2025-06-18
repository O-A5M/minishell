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

char	*expand_token(char *cl, unsigned int *index)
{
	char			*expanded_token;
	unsigned int	start_index;

	*index += 1;
	start_index = *index;
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

// char	*expand_token(char *cl, unsigned int *index, int d_quotes_flag)
// {
// 	char			*expanded_token;
// 	unsigned int	start_index;

// 	*index += 1;
// 	start_index = *index;
// 	d_quotes_flag = 0;
// 	if (is_a_pipe(cl[*index]) || is_a_redir(cl[*index])
// 		|| is_a_whitespace(cl[*index]) || cl[*index] == '\0')
// 	{
// 		return(ft_strdup("$"));
// 	}
// 	else if (is_a_quote(cl[*index]))
// 	{
// 		return(ft_strdup(""));
// 	}
// 	else if (ft_isalpha(cl[*index]) || cl[*index] == '_')
// 	{

// 	}
// 	while (cl[*index])
// 	{

// 	}
// }

// char	*get_expanded_token(char *commandline, unsigned int *current_index)
// {
// 	char			*expanded_token;
// 	unsigned int	start_index;

// 	*current_index += 1;
// 	start_index = *current_index;
// 	if (is_valid_character(commandline[*current_index]))
// 		expanded_token = valid_expansion_token(commandline, &current_index);
// 	else if (is_quote_character(commandline[*current_index]))
// 		expanded_token = ft_strdup("");
// 	else if (commandline[*current_index] == '?')
// 	{
// 		*current_index += 1;
// 		expanded_token = ft_itoa(EXIT_FAILURE);
// 	}
// 	else
// 		expanded_token = ft_strdup("$");
// 	return (expanded_token);
// }
