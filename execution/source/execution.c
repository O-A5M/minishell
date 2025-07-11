/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:53:51 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/11 19:54:26 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	simple_command(t_cmd *cmd, char **env, char **path)
{
	pid_t	child_pid;
	int		i;
	char	*cd;
	char	*path_cmd;
	int		status;

	cd = ft_strjoin("/", cmd->args_array[0]);
	i = find_command(path, cd);
	if (i >= 0)
	{
		path_cmd = ft_strjoin(path[i], cd);
		child_pid = fork ();
		if (child_pid < 0)
			return (TECHNICAL_ERR);
		else if (child_pid == 0)
		{
			if (execve(path_cmd, cmd->args_array, env) == -1)
				return (TECHNICAL_ERR);
		}
		else if (i >= 0)
			waitpid(child_pid, &status, 0);
		free(path_cmd);
		free(cd);
	}
	else
	{
		free(cd);
		return (CMD_N_FOUND);
	}
	return (SUCCES);
}

int	pipe_line(t_cmd *cmd, char **env, char **path)
{
	return (SUCCES);
}

int	start_execution(t_cmd *cmd, char **env, char **path)
{
	simple_command(cmd, env, path);
	return (SUCCES);
}
