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

t_redir_type	what_redirection_type(char *cl, unsigned int *index)
{
	char			redir_char;
	t_redir_type	redir_type;

	redir_char = cl[*index];
	redir_type = -1;
	*index += 1;
	if (cl[*index] == redir_char)
	{
		*index += 1;
		while (is_a_whitespace(cl[*index]))
			*index += 1;
		if (is_a_pipe(cl[*index]) || is_a_redir(cl[*index]) || !cl[*index])
			redirection_error(cl[*index]);
		else
		{
			if (redir_char == '<')
				redir_type = HEREDOC;
			else
				redir_type = APPEND;
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
				redir_type = REDIR_IN;
			else
				redir_type = REDIR_OUT;
		}
	}
	return (redir_type);
}
