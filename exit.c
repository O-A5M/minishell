/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:46:10 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/05/21 11:46:20 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigaction_exit(void)
{
	rl_clear_history();
	perror("Sigaction failed: ");
	exit(1);
}

void	endoffile(void)
{
	rl_clear_history();
	printf("exit\n");
	exit(0);
}

void	allocation_error(void)
{
	printf("Error: Failed to dynamically allocate space.\n");
	exit(1);
}

void	pipe_error(void)
{
	printf("minishell: syntax error near unexpected token `|'\n");
	exit(1);
}

void	redirection_error(char c)
{
	printf("minishell: syntax error near unexpected token `%c'\n", c);
	exit(1);
}

void	unclosed_quotes_error(void)
{
	printf("Parsing Error: Missing Quote Closing Character\n");
	exit(1);
}
