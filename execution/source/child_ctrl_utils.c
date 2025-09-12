/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_ctrl_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:21:06 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/08/16 23:41:50 by oakhmouc         ###   ########.fr       */
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

int	is_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (1);
	return (0);
}

void	dir_message(t_cmd *cmd, char **env, char *cmd_ret)
{
	int	*i;

	i = NULL;
	if (is_directory(cmd_ret))
	{
		ft_putstr_fd(cmd->args_array[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		free_array(env);
		free_export_list((*get_export_list()));
		if (!(*(*get_command()))->next)
		{
			i = (*get_fd_close());
			if (i[0] != -1)
				close(i[0]);
			if (i[1] != -1)
				close(i[1]);
			free_command(&cmd);
			free_array((*get_env_array()));
		}
		else if ((*(*get_command())) && (*(*get_command()))->next)
			free_command((*get_command()));
		free(cmd_ret);
		rl_clear_history();
		exit(126);
	}
}

static int	create_files(t_cmd *cmd, char **path)
{
	t_redir_list	*tmp;

	tmp = cmd->redirections;
	while (tmp)
	{
		if (tmp && tmp->fd != -1)
		{
			dup2(tmp->fd, STDIN_FILENO);
			close(tmp->fd);
		}
		else if (handle_fd(tmp) != SUCCES)
		{
			free_array(path);
			return (TECHNICAL_ERR);
		}
		tmp = tmp->next;
	}
	return (SUCCES);
}

int	redirection_case_pipe(t_cmd *cmd, char **env, char **path
							, t_export **export)
{
	char			*cmd_ret;

	if (create_files(cmd, path) != SUCCES)
		return (TECHNICAL_ERR);
	if (handle_built_ins(cmd, &env, export, path) == SUCCES)
	{
		free_array(path);
		return (SUCCES);
	}
	cmd_ret = search_command(cmd, path);
	free_array(path);
	if (!cmd_ret && !cmd->redirections)
		return (CMD_N_FOUND);
	if (cmd_ret != NULL)
	{
		if (is_directory(cmd_ret))
			dir_message(cmd, env, cmd_ret);
		execve(cmd_ret, cmd->args_array, env);
		return (TECHNICAL_ERR);
	}
	free (cmd_ret);
	exit (SUCCES);
}
