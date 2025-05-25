/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:12:15 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/05/24 12:12:19 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	operator_token(char **cl, size_t *ct)
{
	char	redir;

	if (**cl == '|')
	{
		*cl += 1;
	}
	else
	{
		redir = **cl;
		*cl += 1;
		if (**cl == redir)
			*cl += 1;
	}
	if (**cl == '\0')
		after_operator_error();
	*ct += 1;
}

void	quote_token(char **cl)
{
	char	qt;

	qt = **cl;
	*cl += 1;
	while (**cl && **cl != qt)
	{
		*cl += 1;
	}
	if (**cl != qt)
		unclosed_quotes_error();
	*cl += 1;
}

void	check_flag(char *flag, size_t *ct)
{
	if (*flag)
		*ct += 1;
	*flag = 0;
}

size_t	count_tokens(char *cl)
{
	char	flag;
	size_t	ct;

	flag = 0;
	ct = 0;
	while (*cl)
	{
		while (*cl == ' ' || (*cl >= 9 && *cl <= 13))
			cl++;
		while (*cl && *cl != '>' && *cl != '<' && *cl != '|'
			&& !(*cl >= 9 && *cl <= 13) && *cl != ' ')
		{
			flag = 1;
			if (*cl == '\'' || *cl == '"')
				quote_token(&cl);
			else
				cl++;
		}
		check_flag(&flag, &ct);
		if (*cl == '|' || *cl == '>' || *cl == '<')
			operator_token(&cl, &ct);
	}
	return (ct);
}

char	**tokenizer(char *cl)
{
	char	**tokens;
	size_t	len;

	tokens = NULL;
	len = count_tokens(cl);
	printf("You have %d tokens.\n", (int)len);
	tokens = malloc(sizeof(char *) * (len + 1));
	if (!tokens)
		return (NULL);
	return (tokens);
}
