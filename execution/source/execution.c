/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:53:51 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/06 12:02:10 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int  start_execution(t_cmd *cmd, char **env, char **path)
{
	pid_t	child_pid;
	int		i;
	char	*cd;
	char	*path_cmd;
	int		status;

	child_pid = fork();
	cd = ft_strjoin("/", cmd->args_array[0]);
	i = find_command(path, cd);
	path_cmd = ft_strjoin(path[i], cd);
	if (i < 0 || child_pid < 0)
		return (1);
	else if (child_pid == 0)
	{
		execve(path_cmd, cmd->args_array, env);
		exit (0);
	}
	else if (i >= 0)
		waitpid(child_pid, &status, 0);
	return (0);
}

