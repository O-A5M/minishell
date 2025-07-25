/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:59:30 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/07/25 19:31:59 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

void	handle_signal(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	set_signals(struct sigaction *sa_int, struct sigaction *sa_quit)
{
	sigemptyset(&sa_int->sa_mask);
	sa_int->sa_flags = 0;
	sa_int->sa_handler = handle_signal;
	sigemptyset(&sa_quit->sa_mask);
	sa_quit->sa_flags = 0;
	sa_quit->sa_handler = SIG_IGN;
}
