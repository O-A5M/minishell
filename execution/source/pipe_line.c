/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:53:10 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/19 22:04:59 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

static void	close_fd(int fd1, int fd2)
{
	close (fd1);
	close (fd2);
}

// void	child_work(int flag, int *curr_pipe, int *prev_pipe, t_cmd *cmd)
// {
// 	if (flag)
// 		dup2(prev_pipe[0], STDIN_FILENO);
// 	if (cmd->next)
// 		dup2(curr_pipe[1], STDOUT_FILENO);
// 	if (flag)
// 		close_fd(prev_pipe[1], prev_pipe[0]);
// 	if (cmd->next)
// 		close_fd(curr_pipe[0], curr_pipe[1]);
// }
//
// void	parent_work(int flag, int *curr_pipe, int *prev_pipe, t_cmd *cmd)
// {
// 	if (flag)
// 		close_fd(prev_pipe[0], prev_pipe[1]);
// 	if (cmd->next)
// 	{
// 		prev_pipe[0] = curr_pipe[0];
// 		prev_pipe[1] = curr_pipe[1];
// 		flag = 1;
// 	}
// }

// int	pipe_line(t_cmd *cmd, char **env, char **path)
// {
// 	int		prev_pipe[2];
// 	int		curr_pipe[2];
// 	int		has_prev;
// 	pid_t	pid;
// 	char	*cmd_ret;
//
// 	has_prev = 0;
// 	while (cmd)
// 	{
// 		cmd_ret = search_command(cmd, path);
// 		if (cmd->next && pipe(curr_pipe) == -1)
// 			return (TECHNICAL_ERR);
// 		pid = fork();
// 		if (pid == -1)
// 			return (TECHNICAL_ERR);
// 		else if (pid == 0)
// 		{
// 			child_work(has_prev, curr_pipe, prev_pipe, cmd);
// 			simple_command(cmd, env, path);
// 		}
// 		else
// 			parent_work(has_prev, curr_pipe, prev_pipe, cmd);
// 		free(cmd_ret);
// 		cmd = cmd->next;
// 	}
// 	while (wait(NULL));
// 	return (SUCCES);
// }


int	pipe_line(t_cmd *cmd, char **env, char **path)
{
	int		prev_pipe[2];
	int		curr_pipe[2];
	int		has_prev;
	pid_t	pid;
	char	*ret_cmd;

	has_prev = 0;
	while (cmd)
	{
		if (pipe(curr_pipe) == -1)
			return (TECHNICAL_ERR);
		ret_cmd = search_command(cmd, path);
		pid = fork();
		if (pid == -1)
			return (TECHNICAL_ERR);
		else if (pid == 0)
		{
			if (has_prev)
				dup2(prev_pipe[0], STDIN_FILENO);
			if (cmd->next)
				dup2(curr_pipe[1], STDOUT_FILENO);
			if (has_prev)
				close_fd(prev_pipe[0], prev_pipe[1]);
			if (cmd->next)
				close_fd(curr_pipe[0], curr_pipe[1]);
			execve(ret_cmd, cmd->args_array, env);
			return (TECHNICAL_ERR);
		}
		if (has_prev)
			close_fd(prev_pipe[0], prev_pipe[1]);
		if (cmd->next)
		{
			prev_pipe[0] = curr_pipe[0];
			prev_pipe[1] = curr_pipe[1];
			has_prev = 1;
		}
		free(ret_cmd);
		cmd = cmd->next;
	}
	while (wait(NULL) > 0);
	return (SUCCES);
}
