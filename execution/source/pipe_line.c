/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:53:10 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/26 18:32:22 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

int	redirection_case_pipe(t_cmd *cmd, char **env, char **path)
{
	char	*cmd_ret;

	while (cmd->redirections)
	{
		if (handle_fd(cmd->redirections) != SUCCES)
			return (TECHNICAL_ERR);
		cmd->redirections = cmd->redirections->next;
	}
	if (handle_built_ins(cmd, &env) == SUCCES)
		return (SUCCES);
	cmd_ret = search_command(cmd, path);
	if (!cmd_ret && !cmd->redirections)
		exit (CMD_N_FOUND);
	if (cmd_ret != NULL)
	{
		execve(cmd_ret, cmd->args_array, env);
		return (TECHNICAL_ERR);
	}
	free (cmd_ret);
	exit (SUCCES);
}

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

static void	exit_msg(int status)
{
	if (status == CMD_N_FOUND)
	{
		ft_putstr_fd("Command not found\n", 2);
		exit (CMD_N_FOUND);
	}
	else
		exit (status);
}

int	pipe_line(t_cmd *cmd, char **env, char **path)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	while (cmd)
	{
		if ((cmd->next && pipe(fd) == -1) || (pid = fork()) == -1)
			return (TECHNICAL_ERR);
		else if (pid == 0)
		{
			child_work(prev_fd, fd, cmd);
			exit_msg(redirection_case_pipe(cmd, env, path));
		}
		parent_work(&prev_fd, fd, cmd);
		cmd = cmd->next;
	}
	while (wait(NULL) > 0);
	return (SUCCES);
}
