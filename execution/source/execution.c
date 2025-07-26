/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:53:51 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/26 18:46:10 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	reset_signal(int flag)
{
	if (flag == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

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

static int	child_work(t_cmd *cmd, char **env, char *cmd_ret)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		return (TECHNICAL_ERR);
	else if (pid == 0)
	{
		reset_signal(1);
		execve(cmd_ret, cmd->args_array, env);
		exit (TECHNICAL_ERR);
	}
	else
	{
		waitpid(pid, &return_status, 0);
		if (WIFEXITED(return_status))
			return (WEXITSTATUS(return_status));
		else if (WIFSIGNALED(return_status))
			return (128 + WTERMSIG(return_status));
		return (return_status);
	}
	return (SUCCES);
}

int	redirection_case_sc(t_cmd *cmd, char **env, char **path)
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
		return (CMD_N_FOUND);
	if (cmd_ret)
	{
		reset_signal(0);
		return (child_work(cmd, env, cmd_ret));
	}
	return (SUCCES);
}

int	simple_command(t_cmd *cmd, char **env, char **path)
{
	int	ret;

	ret = redirection_case_sc(cmd, env, path);
	return (ret);
}

int	start_execution(t_cmd *cmd, char ***m_env)
{
	char	**path;

	path = split_path(*m_env);
	if (cmd->next)
		return_status = pipe_line(cmd, *m_env, path);
	else
		return_status = simple_command(cmd, *m_env, path);
	if (return_status == CMD_N_FOUND)
		ft_putstr_fd("Command not found\n", 2);
	free_array(path);
	return (return_status);
}
