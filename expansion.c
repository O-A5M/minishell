/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_real_tokenizer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:44:59 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/06/02 15:45:02 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_text_chunk(char *text_chunk, char **dst)
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

char	*valid_expansion_token(char *commandline, unsigned int *index)
{
	char			*variable_name;
	char			*expanded_variable;
	unsigned int	start_index;

	start_index = *index;
	while (commandline[*index] == '_' || ft_isalnum(commandline[*index]))
		*index += 1;
	variable_name = ft_substr(commandline, start_index, *index - start_index);
	expanded_variable = getenv(variable_name);
	free(variable_name);
	if (expanded_variable == NULL)
		expanded_variable = ft_strdup("");
	return (expanded_variable);
}

char	*get_expanded_token(char *commandline, unsigned int *current_index)
{
	char			*expanded_token;
	unsigned int	start_index;

	*current_index += 1;
	start_index = *current_index;
	if (is_valid_character(commandline[*current_index]))
		expanded_token = valid_expansion_token(commandline, &current_index);
	else if (is_quote_character(commandline[*current_index]))
		expanded_token = ft_strdup("");
	else if (commandline[*current_index] == '?')
	{
		*current_index += 1;
		expanded_token = ft_itoa(EXIT_FAILURE);
	}
	else
		expanded_token = ft_strdup("$");
	return (expanded_token);
}

char	*quoted_text_expander(char *quoted_text)
{
	unsigned int	start_index;
	unsigned int	current_index;
	char			*text_chunk;
	char			*expanded_quoted_text;

	expanded_quoted_text = NULL;
	current_index = 0;
	while (quoted_text[current_index])
	{
		start_index = current_index;
		while (quoted_text[current_index] != '\0'
			&& quoted_text[current_index] != '$')
			current_index += 1;
		add_text_chunk(ft_substr(quoted_text, start_index,
				current_index - start_index), &expanded_quoted_text);
		if (quoted_text[current_index] != '\0')
			add_text_chunk(get_expanded_token(quoted_text, &current_index),
				&expanded_quoted_text);
	}
	if (expanded_quoted_text == NULL)
		return (quoted_text);
	free(quoted_text);
	return (expanded_quoted_text);
}
