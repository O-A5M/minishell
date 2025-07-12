/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:53:51 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/12 06:38:52 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

char	*search_command(t_cmd *cmd, char **path)
{
	char	*ret;
	int		index;
	char	*tmp;

	ret = NULL;
	tmp = NULL;
	index = -1;
	if (ft_strchr(cmd->args_array[0], '/'))
	{
		if (access(cmd->args_array[0], X_OK) == 0)
			return (ft_strdup(cmd->args_array[0]));
	}
	else
	{
		tmp = ft_strjoin("/", cmd->args_array[0]);
		while (path[++index])
		{
			ret = ft_strjoin(path[index], tmp);
			if (access(ret, X_OK) == 0)
				return (ret);
		}
	}
	free (ret);
	free (tmp);
	return (NULL);
}

int	simple_command(t_cmd *cmd, char **env, char **path)
{
	int		child_pid;
	int		i;
	char 	*ret_cmd;

	ret_cmd = search_command(cmd, path);
	i = 0;
	if (ret_cmd)
	{
		child_pid = fork ();
		if (child_pid < 0)
			return (TECHNICAL_ERR);
		else if (child_pid == 0)
		{
			if (execve(ret_cmd, cmd->args_array, env) == -1)
				return (TECHNICAL_ERR);
		}
		else if (i >= 0)
			wait(NULL);
		free (ret_cmd);
	}
	else
		return (CMD_N_FOUND);
	return (SUCCES);
}

int	pipe_line(t_cmd *cmd, char **env, char **path)
{
	int prev_pipe[2];
	int curr_pipe[2];
	int has_prev = 0;
	pid_t pid;
	char *ret_cmd;

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
			{
				close(prev_pipe[0]);
				close(prev_pipe[1]);
			}
			if (cmd->next)
			{
				close(curr_pipe[0]);
				close(curr_pipe[1]);
			}
			execve(ret_cmd, cmd->args_array, env);
			return (TECHNICAL_ERR);
		}
		free(ret_cmd);
		if (has_prev)
		{
			close(prev_pipe[0]);
			close(prev_pipe[1]);
		}
		if (cmd->next)
		{
			prev_pipe[0] = curr_pipe[0];
			prev_pipe[1] = curr_pipe[1];
			has_prev = 1;
		}
		else
			has_prev = 0;
		cmd = cmd->next;
	}
	while (wait(NULL) > 0)
		;
	return (SUCCES);
}

int	start_execution(t_cmd *cmd, char **env, char **path)
{
	if (cmd->next)
		pipe_line(cmd, env, path);
	else
		simple_command(cmd, env, path);
	return (SUCCES);
}
