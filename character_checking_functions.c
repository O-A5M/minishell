/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_checking_functions.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:44:23 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/06/02 16:44:24 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace_character(char c)
{
	if (c == ' ' || c >= 9 && c <= 13)
		return (1);
	else
		return (0);
}

int	is_quote_character(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	else
		return (0);
}

int	is_meta_character(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}

int	is_valid_character(char c)
{
	if (c == '_' || ft_isalpha(c))
		return (1);
	else
		return (0);
}
