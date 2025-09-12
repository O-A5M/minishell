/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:46:10 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/16 23:32:34 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
}

void	redirection_error(char c)
{
	if (c == '\0')
		ft_putstr_fd("minishell: syntax error near unexpected \
token `newline'\n", 2);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token`", 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("'\n", 2);
	}
}

void	unclosed_quotes_error(void)
{
	ft_putstr_fd("Parsing Error: Missing Quote Closing Character\n", 2);
}

int	open_error(void)
{
	perror("Error");
	return (-1);
}

int	fork_error(void)
{
	perror("Error");
	return (-1);
}
