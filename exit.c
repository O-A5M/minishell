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
