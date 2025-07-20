/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:53:10 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/20 16:52:34 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_work(int prev_fd, int	*fd, t_cmd *cmd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
}

void	parent_work(int *prev_fd, int *fd, t_cmd *cmd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
}

int	pipe_line(t_cmd *cmd, char **env, char **path)
{
	int		fd[2];
	int		prev_fd;
	char	*cmd_ret;
	pid_t	pid;

	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
			return (TECHNICAL_ERR);
		cmd_ret = search_command(cmd, path);
		if ((pid = fork()) == -1)
			return (TECHNICAL_ERR);
		else if (pid == 0)
		{
			child_work(prev_fd, fd, cmd);
			execve(cmd_ret, cmd->args_array, env);
			return (TECHNICAL_ERR);
		}
		free (cmd_ret);
		parent_work(&prev_fd, fd, cmd);
		cmd = cmd->next;
	}
	while (wait(NULL) > 0);
	return (SUCCES);
}
