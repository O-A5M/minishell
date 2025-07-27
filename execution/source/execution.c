/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:53:51 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/27 17:45:15 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

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
	}
	return (SUCCES);
}

void	restore_fd(int fd0, int fd1)
{
	dup2(fd0, STDIN_FILENO);
	dup2(fd1, STDOUT_FILENO);
	close(fd0);
	close(fd1);
}

int	redirection_case_sc(t_cmd *cmd, char **env, char **path, t_export **export)
{
	char	*cmd_ret;
	int		ret;
	int		fd[2];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	while (cmd->redirections)
	{
		if (handle_fd(cmd->redirections) != SUCCES)
			return (TECHNICAL_ERR);
		cmd->redirections = cmd->redirections->next;
	}
	if ((ret = handle_built_ins(cmd, &env, export)) != CMD_N_FOUND)
		return (restore_fd(fd[0], fd[1]), ret);
	cmd_ret = search_command(cmd, path);
	if (!cmd_ret && !cmd->redirections)
		return (restore_fd(fd[0], fd[1]), CMD_N_FOUND);
	if (cmd_ret)
	{
		reset_signal(0);
		ret = child_work(cmd, env, cmd_ret);
		return (restore_fd(fd[0], fd[1]), ret);
	}
	return (SUCCES);
}

int	simple_command(t_cmd *cmd, char **env, char **path, t_export **export)
{
	int	ret;

	ret = redirection_case_sc(cmd, env, path, export);
	return (ret);
}

int	start_execution(t_cmd *cmd, t_export **export)
{
	char	**path;
	char	**m_env;

	m_env = env_to_arr(*export);
	path = split_path(m_env);
	if (cmd->next)
		return_status = pipe_line(cmd, m_env, path, export);
	else
		return_status = simple_command(cmd, m_env, path, export);
	if (return_status == CMD_N_FOUND)
		ft_putstr_fd("Command not found\n", 2);
	free_array(path);
	free_array(m_env);
	return (return_status);
}
