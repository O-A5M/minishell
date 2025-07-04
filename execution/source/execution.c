/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:53:51 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/04 22:19:50 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../../minishell.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// char	*get_path(char *cmd, char **path)
// {
// 	char	*ret;
//
//
// }
//
int	fined_command(char **path, char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (path[i])
	{
		str = ft_strjoin(path[i], s);
		if (access(str, X_OK) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int  start_execution(t_cmd *cmd, char **env, char **path)
{
	pid_t	child_pid;
	int		i;
	char	*cd;
	char	*path_cmd;

	child_pid = fork();
	cd = ft_strjoin("/", cmd->args_array[0]);
	i = fined_command(path, cd);
	path_cmd = ft_strjoin(path[i], cd);
	if (child_pid < 0)
		return (1);
	else if (child_pid == 0)
	{
		execve(path_cmd, cmd->args_array, env);
		exit (0);
	}
	else
	{
		int	status;
		waitpid(child_pid, &status, 0);
	}
	return (0);
}

