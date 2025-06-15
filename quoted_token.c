/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:21:10 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/06/02 17:21:12 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_text(char *text_chunk, char **dst)
{
	char	*old_dst;

	old_dst = *dst;
	if (*dst == NULL)
		*dst = ft_strdup(text_chunk);
	else
		*dst = ft_strjoin(*dst, text_chunk);
	free(old_dst);
	free(text_chunk);
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
	expanded_variable = getenv(variable_name);
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

char	*expand_quoted_text(char *quoted_text)
{
	unsigned int	start_index;
	unsigned int	index;
	char			*text_chunk;
	char			*expanded_quoted_text;

	expanded_quoted_text = NULL;
	index = 0;
	while (quoted_text[index] != '\0')
	{
		start_index = index;
		while (quoted_text[index] != '\0' && quoted_text[index] != '$')
			index += 1;
		add_text(ft_substr(quoted_text, start_index,
				index - start_index), &expanded_quoted_text);
		// does it also copy the `$` character, that'd be a problem???
		if (quoted_text[index] != '\0')
			add_text(expand_token(quoted_text, &index),
				&expanded_quoted_text);
	}
	if (expanded_quoted_text == NULL)
		return (quoted_text);
	free(quoted_text);
	return (expanded_quoted_text);
}

char	*get_quoted_token(char *cl, unsigned int *index)
{
	unsigned int	start_index;
	char			*quoted_text;
	char			quote_sign;

	quote_sign = cl[*index];
	*index += 1;
	start_index = *index;
	while (cl[*index] != '\0' && cl[*index] != quote_sign)
		*index += 1;
	if (cl[*index] == '\0')
		unclosed_quotes_error();
	quoted_text = ft_substr(cl, start_index, *index - start_index);
	*index += 1;
	if (quote_sign == '"')
		quoted_text = expand_quoted_text(quoted_text);
	return (quoted_text);
}
