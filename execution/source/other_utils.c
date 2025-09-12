/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:54:18 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/08/16 23:37:18 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	wait_child(pid_t pid)
{
	waitpid(pid, &g_return_status, 0);
	if (WIFEXITED(g_return_status))
		return (WEXITSTATUS(g_return_status));
	else if (WIFSIGNALED(g_return_status))
		return (write(1, "\n", 1), (128 + WTERMSIG(g_return_status)));
	return (g_return_status);
}

void	restore_fd(int fd0, int fd1)
{
	dup2(fd0, STDIN_FILENO);
	dup2(fd1, STDOUT_FILENO);
	if (fd0 != -1)
		close(fd0);
	if (fd1 != -1)
		close(fd1);
}
