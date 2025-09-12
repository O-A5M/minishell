/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_token_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:21:56 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/08/15 20:41:42 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_signal_handler(int signum)
{
	g_return_status = signum + 128;
	free_command(*get_command());
	free_export_list(*get_export_list());
	free_array(*get_env_array());
	close(*get_fd());
	printf("\n");
	rl_clear_history();
	exit(130);
}

// Setup / Change Behavior When Signal Received
void	ignore_parent_signal(t_cmd **command)
{
	struct sigaction	sa_int;

	sigemptyset(&(sa_int.sa_mask));
	sa_int.sa_flags = 0;
	sa_int.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		sigaction_exit(command);
}

void	parent_signal_back(t_cmd **command)
{
	struct sigaction	sa_int;

	sigemptyset(&(sa_int.sa_mask));
	sa_int.sa_flags = 0;
	sa_int.sa_handler = handle_signal;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		sigaction_exit(command);
}

// Setup / Change Behavior When Signal Received
void	setup_heredoc_signal(t_cmd **command)
{
	struct sigaction	sa_int;

	sigemptyset(&(sa_int.sa_mask));
	sa_int.sa_flags = 0;
	sa_int.sa_handler = child_signal_handler;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		sigaction_exit(command);
}

int	simple_cases(char *filename, char *token)
{
	if (num_of_fields(token) > 1)
		return (1);
	if (filename && one_field_starts_with_ifs(token))
		return (1);
	return (0);
}
