/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:03:17 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/06/04 15:03:18 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	is_a_pipe(char c)
{
	if (c == '|')
		return (1);
	else
		return (0);
}

int	is_a_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	else
		return (0);
}

t_redir_type	what_redirection_type(char *cl, int *index)
{
	char	redir_char;

	redir_char = cl[*index];
	*index += 1;
	if (cl[*index] == redir_char)
	{
		while (is_a_whitespace(cl[*index]))
			*index += 1;
		if (is_a_pipe(cl[*index]) || is_a_redir(cl[*index]) || !cl[*index])
			redirection_error(cl[*index]);
		else
		{
			if (redir_char == '<')
				return (HEREDOC);
			else
				return (APPEND);
		}
	}
	else
	{
		while (is_a_whitespace(cl[*index]))
			*index += 1;
		if (is_a_pipe(cl[*index]) || is_a_redir(cl[*index]) || !cl[*index])
			redirection_error(cl[*index]);
		else
		{
			if (redir_char == '<')
				return (REDIR_IN);
			else
				return (REDIR_OUT);
		}
	}
}
