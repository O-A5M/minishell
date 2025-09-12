/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:07:13 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/08/17 00:09:53 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

char	*check_command(t_cmd *cmd, char **path)
{
	char	*ret;
	char	*tmp;
	int		index;

	ret = NULL;
	tmp = NULL;
	index = -1;
	if (cmd->args_array[0][0] != '\0')
		tmp = ft_strjoin("/", cmd->args_array[0]);
	while (path[++index])
	{
		ret = ft_strjoin(path[index], tmp);
		if (access(ret, X_OK) == 0)
		{
			free(tmp);
			return (ret);
		}
		free (ret);
	}
	free (tmp);
	return (NULL);
}

char	*search_command(t_cmd *cmd, char **path)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	tmp = NULL;
	if (!path)
		return (NULL);
	if (!cmd->args_array[0] || cmd->args_array[0][0] == '\0')
		return (NULL);
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

static int	create_files(t_redir_list *redir, int *fd)
{
	if (redir->filename && redir->filename[0] == '\0')
	{
		ft_putstr_fd(" : No such file or directory\n", 2);
		return (TECHNICAL_ERR);
	}
	if (redir->redir_type == REDIR_OUT)
		redir_out(redir, fd);
	else if (redir->redir_type == REDIR_IN)
		redir_inp(redir, fd);
	else if (redir->redir_type == APPEND)
		redir_app(redir, fd);
	if ((*fd) == -1)
		return (perror("Error"), TECHNICAL_ERR);
	return (SUCCES);
}

int	handle_fd(t_redir_list *redir)
{
	int	fd;

	fd = -1;
	if (redir->ambiguous_flag)
	{
		ft_putstr_fd(redir->literal_filename, 2);
		ft_putstr_fd(": ambiguous_redirect\n", 2);
		return (TECHNICAL_ERR);
	}
	if (create_files(redir, &fd) != SUCCES)
		return (TECHNICAL_ERR);
	if (fd != -1)
		close(fd);
	return (SUCCES);
}
