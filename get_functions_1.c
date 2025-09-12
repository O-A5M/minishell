/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:22:24 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/08/16 23:30:16 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*retrieve_token(char **unquoted_text, char *delimiter,
			unsigned int start, unsigned int i)
{
	char	*part;

	part = ft_substr(delimiter, start, i - start);
	*unquoted_text = add_text(part, *unquoted_text);
	return (*unquoted_text);
}

// Remove the quotes from the delimiter to heredoc.
char	*remove_quotes(char *delimiter)
{
	unsigned int	i;
	unsigned int	start;
	char			quote_sign;
	char			*unquoted_text;

	i = 0;
	unquoted_text = NULL;
	while (delimiter[i])
	{
		start = i;
		while (delimiter[i] && !is_a_quote(delimiter[i]))
			i++;
		retrieve_token(&unquoted_text, delimiter, start, i);
		if (!delimiter[i])
			break ;
		quote_sign = delimiter[i++];
		start = i;
		while (delimiter[i] && delimiter[i] != quote_sign)
			i++;
		if (!delimiter[i])
			return (free(delimiter), free(unquoted_text), NULL);
		retrieve_token(&unquoted_text, delimiter, start, i);
		i++;
	}
	return (free(delimiter), unquoted_text);
}
