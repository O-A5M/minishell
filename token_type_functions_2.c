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

int	is_an_expansion(char c)
{
	if (c == '$')
		return (1);
	else
		return (0);
}

int	is_a_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	else
		return (0);
}

int	is_other(char c)
{
	if (!is_a_quote(c) && !is_a_pipe(c) && !is_a_redir(c)
		&& !is_a_whitespace(c) && !is_an_expansion(c) && c != '\0')
		return (1);
	else
		return (0);
}
