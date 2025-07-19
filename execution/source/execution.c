/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:53:51 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/19 16:46:22 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

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

int	start_execution(t_cmd *cmd, char **m_env)
{
	char	**path;

	if (!cmd->args_array[0])
		return (SUCCES);
	path = split_path(m_env);
	if (cmd->next)
		pipe_line(cmd, m_env, path);
	else
		simple_command(cmd, m_env, path);
	free_array(path);
	return (SUCCES);
}
