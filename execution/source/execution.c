/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:53:51 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/25 18:41:38 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	handle_fd(t_redir_list *redir)
{
	int	fd;

	fd = -1;
	if (redir->redir_type == REDIR_OUT)
	{
		if ((fd = open(redir->filename, O_CREAT | O_RDWR | O_TRUNC
				 , 0644)) != -1)
			dup2(fd, STDOUT_FILENO);
	}
	else if (redir->redir_type == REDIR_IN)
	{
		if ((fd = open(redir->filename, O_RDONLY, 0644)) != -1)
			dup2(fd, STDIN_FILENO);
		else
		{
			write(2, "No such file or directory\n", 26);
			return (TECHNICAL_ERR);
		}
	}
	else if (redir->redir_type == APPEND)
	{
		if ((fd = open(redir->filename, O_CREAT | O_APPEND | O_RDWR
				 , 0644)) != -1)
			dup2(fd, STDOUT_FILENO);
	}
	if (fd == -1)
		return (TECHNICAL_ERR);
	close(fd);
	return (SUCCES);
}

int	redirection_case(t_cmd *cmd, char **env, char **path)
{
	char	*cmd_ret;

	while (cmd->redirections)
	{
		if (handle_fd(cmd->redirections) != SUCCES)
			return (TECHNICAL_ERR);
		cmd->redirections = cmd->redirections->next;
	}
	cmd_ret = search_command(cmd, path);
	if (cmd_ret != NULL)
	{
		if (handle_built_ins(cmd, &env) == SUCCES)
			return (SUCCES);
		execve(cmd_ret, cmd->args_array, env);
		return (TECHNICAL_ERR);
	}
	free (cmd_ret);
	exit (SUCCES);
}

int	simple_command(t_cmd *cmd, char **env, char **path)
{
	int		child_pid;
	int		i;

	i = 0;
	child_pid = fork ();
	if (child_pid < 0)
		return (TECHNICAL_ERR);
	else if (child_pid == 0)
	{
		if (redirection_case(cmd, env, path) == TECHNICAL_ERR)
			exit (TECHNICAL_ERR);
		exit (SUCCES);
	}
	else if (i >= 0)
		wait(NULL);
	return (SUCCES);
}

int	start_execution(t_cmd *cmd, char ***m_env)
{
	char	**path;

	path = NULL;
	path = split_path(*m_env);
	// if (!cmd->args_array[0])
	// 	return (redirection_case(cmd, *m_env, path));
	if (cmd->next)
		pipe_line(cmd, *m_env, path);
	else
		simple_command(cmd, *m_env, path);
	free_array(path);
	return (SUCCES);
}
