/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:53:51 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/08/17 00:26:08 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

static int	child_work(t_cmd *cmd, char **env, char *cmd_ret, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (restore_fd(fd[0], fd[1]), TECHNICAL_ERR);
	else if (pid == 0)
	{
		reset_signal(1);
		if (is_directory(cmd_ret))
		{
			dir_message(cmd, env, cmd_ret);
		}
		execve(cmd_ret, cmd->args_array, env);
		restore_fd(fd[0], fd[1]);
		exit (TECHNICAL_ERR);
	}
	else
		return (restore_fd(fd[0], fd[1]), wait_child(pid));
	return (restore_fd(fd[0], fd[1]), SUCCES);
}

static int	check_red(t_cmd *cmd)
{
	t_redir_list	*tmp;

	tmp = cmd->redirections;
	while (tmp)
	{
		if (tmp && tmp->redir_type == HEREDOC && tmp->fd != -1)
		{
			dup2(tmp->fd, STDIN_FILENO);
			close(tmp->fd);
		}
		else if (handle_fd(tmp) != SUCCES)
			return (TECHNICAL_ERR);
		tmp = tmp->next;
	}
	return (SUCCES);
}

int	redirection_case_sc(t_cmd *cmd, char **env, char **path, t_export **export)
{
	char			*cmd_ret;
	int				ret;
	int				fd[2];

	fd[1] = dup(STDOUT_FILENO);
	fd[0] = dup(STDIN_FILENO);
	*get_fd_close() = fd;
	if (check_red(cmd) != SUCCES)
		return (restore_fd(fd[0], fd[1]), TECHNICAL_ERR);
	ret = handle_built_ins(cmd, &env, export, path);
	if (ret != CMD_N_FOUND)
		return (restore_fd(fd[0], fd[1]), ret);
	cmd_ret = search_command(cmd, path);
	if (!cmd_ret)
		return (restore_fd(fd[0], fd[1]), CMD_N_FOUND);
	if (cmd_ret)
	{
		reset_signal(0);
		ret = child_work(cmd, env, cmd_ret, fd);
		return (free(cmd_ret), restore_fd(fd[0], fd[1]), ret);
	}
	return (restore_fd(fd[0], fd[1]), SUCCES);
}

int	simple_command(t_cmd *cmd, char **env, char **path, t_export **export)
{
	int	ret;

	(*get_command()) = &cmd;
	ret = redirection_case_sc(cmd, env, path, export);
	return (ret);
}

int	start_execution(t_cmd *cmd, t_export **export)
{
	char	**path;
	char	**m_env;

	m_env = env_to_arr(*export);
	path = split_path(m_env);
	(*get_export_list()) = (*export);
	(*get_env_array()) = path;
	if (cmd->next)
		g_return_status = pipe_line(cmd, m_env, path, export);
	else
	{
		g_return_status = simple_command(cmd, m_env, path, export);
		if (g_return_status == CMD_N_FOUND)
		{
			ft_putstr_fd(cmd->args_array[0], 2);
			ft_putstr_fd(": Command not found\n", 2);
		}
	}
	free_array(path);
	free_array(m_env);
	return (g_return_status);
}
