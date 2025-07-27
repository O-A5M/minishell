/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:21:10 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/07/24 17:39:03 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_text(char *text_chunk, char *dst)
{
	char	*result;

	if (dst == NULL)
	{
		result = ft_strdup(text_chunk);
		free(text_chunk);
	}
	else
	{
		result = ft_strjoin(dst, text_chunk);
		free(text_chunk);
		free(dst);
	}
	return (result);
}

char	*expand_quoted_text(char *quoted_text, char **env)
{
	unsigned int	start_index;
	unsigned int	index;
	char			*expanded_quoted_text;

	expanded_quoted_text = NULL;
	index = 0;
	while (quoted_text[index] != '\0')
	{
		start_index = index;
		while (quoted_text[index] != '\0' && quoted_text[index] != '$')
			index += 1;
		expanded_quoted_text = add_text(ft_substr(quoted_text, start_index,
					index - start_index), expanded_quoted_text);
		if (quoted_text[index] != '\0')
			expanded_quoted_text
				= add_text(get_expanded_token(quoted_text, &index, env),
					expanded_quoted_text);
	}
	if (expanded_quoted_text == NULL)
		return (quoted_text);
	free(quoted_text);
	return (expanded_quoted_text);
}

char	*get_quoted_token(char *cl, unsigned int *index, char **env)
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
	{
		unclosed_quotes_error();
		return (NULL);
	}
	quoted_text = ft_substr(cl, start_index, *index - start_index);
	*index += 1;
	if (quote_sign == '"')
		quoted_text = expand_quoted_text(quoted_text, env);
	return (quoted_text);
}
