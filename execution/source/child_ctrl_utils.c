/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_ctrl_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:21:06 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/28 16:25:37 by oakhmouc         ###   ########.fr       */
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

void	restore_fd(int fd0, int fd1)
{
	dup2(fd0, STDIN_FILENO);
	dup2(fd1, STDOUT_FILENO);
	close(fd0);
	close(fd1);
}

int	is_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (1);
	return (0);
}

void	dir_message(char *cmd_path)
{
	if (is_directory(cmd_path))
	{
		ft_putstr_fd(cmd_path, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
}
