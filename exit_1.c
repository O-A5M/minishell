/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:46:10 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/07/06 17:49:17 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigaction_exit(void)
{
	rl_clear_history();
	perror("Sigaction failed: ");
}

void	endoffile(t_cmd **command)
{
	rl_clear_history();
	printf("exit\n");
	free_command(command);
	exit(0);
}

void	allocation_error(void)
{
	printf("Error: Failed to dynamically allocate space.\n");
}
