/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:46:10 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/07/06 17:49:33 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_error(void)
{
	printf("minishell: syntax error near unexpected token `|'\n");
}

void	redirection_error(char c)
{
	if (c == '\0')
		printf("minishell: syntax error near unexpected token `newline'\n");
	else
		printf("minishell: syntax error near unexpected token `%c'\n", c);
}

void	unclosed_quotes_error(void)
{
	printf("Parsing Error: Missing Quote Closing Character\n");
}
