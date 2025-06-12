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
