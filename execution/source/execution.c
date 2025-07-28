/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:53:51 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/28 15:29:37 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	child_work(t_cmd *cmd, char **env, char *cmd_ret)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (TECHNICAL_ERR);
	else if (pid == 0)
	{
		reset_signal(1);
		if (is_directory(cmd_ret))
			dir_message(cmd_ret);
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
	ret = handle_built_ins(cmd, &env, export);
	if (ret != CMD_N_FOUND)
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
