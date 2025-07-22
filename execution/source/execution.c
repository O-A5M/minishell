/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:53:51 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/22 18:08:19 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	redirection_case(t_cmd *cmd, char *cmd_ret, char **env)
{
	while (cmd->redirections)
	{
		if (handle_fd(cmd->redirections) != SUCCES)
			return (TECHNICAL_ERR);
		cmd->redirections = cmd->redirections->next;
	}
	execve(cmd_ret, cmd->args_array, env);
	return (TECHNICAL_ERR);
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
			if (redirection_case(cmd, ret_cmd, env) == TECHNICAL_ERR)
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

int	start_execution(t_cmd *cmd, char **m_env)
{
	char	**path;

	if (!cmd->args_array[0])
		return (SUCCES);
	if (!handle_built_ins(cmd, m_env))
		return (SUCCES);
	path = split_path(m_env);
	if (cmd->next)
		pipe_line(cmd, m_env, path);
	else
		simple_command(cmd, m_env, path);
	free_array(path);
	return (SUCCES);
}
