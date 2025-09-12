/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:59:30 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/07/29 16:10:58 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_return_status = 130;
	return ;
}

void	setup_main(struct sigaction *sa_int, struct sigaction *sa_quit,
			t_cmd **command, t_export **export)
{
	sigemptyset(&(sa_int->sa_mask));
	sa_int->sa_flags = 0;
	sa_int->sa_handler = handle_signal;
	sigemptyset(&(sa_quit->sa_mask));
	sa_quit->sa_flags = 0;
	sa_quit->sa_handler = SIG_IGN;
	*command = NULL;
	*export = NULL;
}
