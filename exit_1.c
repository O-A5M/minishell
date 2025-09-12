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

void	sigaction_exit(t_cmd **command)
{
	rl_clear_history();
	free_command(command);
	perror("Sigaction");
	exit(1);
}

void	endoffile(t_cmd **command, t_export *export)
{
	free_command(command);
	free_export_list(export);
	printf("exit\n");
	rl_clear_history();
	exit(g_return_status);
}

void	heredoc_eof_warning(char *dlmtr)
{
	printf("minishell: warning: here-document delimited by end-of-file \
(wanted `%s')\n", dlmtr);
}
