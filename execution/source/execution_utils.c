/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:07:13 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/28 16:53:24 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <string.h>

char	*check_command(t_cmd *cmd, char **path)
{
	char	*ret;
	char	*tmp;
	int		index;

	ret = NULL;
	tmp = NULL;
	index = -1;
	tmp = ft_strjoin("/", cmd->args_array[0]);
	if (is_directory(tmp))
		return (tmp);
	while (path[++index])
	{
		ret = ft_strjoin(path[index], tmp);
		if (access(ret, X_OK) == 0)
		{
			free(tmp);
			return (ret);
		}
	}
	free (tmp);
	free (ret);
	return (NULL);
}

char	*search_command(t_cmd *cmd, char **path)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	tmp = NULL;
	if (!cmd->args_array[0] || cmd->args_array[0][0] == '\0')
		return (NULL);
	if (cmd->args_array[0][0] && is_directory(cmd->args_array[0]))
		return (strdup(cmd->args_array[0]));
	if (ft_strchr(cmd->args_array[0], '/'))
	{
		if (access(cmd->args_array[0], X_OK) == 0)
			return (ft_strdup(cmd->args_array[0]));
	}
	else
		return (check_command(cmd, path));
	free (ret);
	free (tmp);
	return (NULL);
}

static int	redir_in_case(t_redir_list *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY, 0644);
	if (fd != -1)
		dup2(fd, STDIN_FILENO);
	else
	{
		write(2, "No such file or directory\n", 26);
		return (TECHNICAL_ERR);
	}
	return (SUCCES);
}

int	handle_fd(t_redir_list *redir)
{
	int	fd;

	fd = -1;
	if (redir->redir_type == REDIR_OUT)
	{
		fd = open(redir->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd != -1)
			dup2(fd, STDOUT_FILENO);
	}
	else if (redir->redir_type == REDIR_IN)
		return (redir_in_case(redir));
	else if (redir->redir_type == APPEND)
	{
		fd = open(redir->filename, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (fd != -1)
			dup2(fd, STDOUT_FILENO);
	}
	if (fd == -1)
		return (TECHNICAL_ERR);
	close(fd);
	return (SUCCES);
}
