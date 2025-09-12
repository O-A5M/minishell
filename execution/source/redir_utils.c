/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:52:54 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/08/17 00:05:10 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redir_out(t_redir_list *redir, int *fd)
{
	(*fd) = open(redir->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if ((*fd) != -1)
	{
		dup2((*fd), STDOUT_FILENO);
		close (*fd);
	}
}

void	redir_app(t_redir_list *redir, int *fd)
{
	(*fd) = open(redir->filename, O_CREAT | O_APPEND | O_RDWR, 0644);
	if ((*fd) != -1)
	{
		dup2((*fd), STDOUT_FILENO);
		close(*fd);
	}
}

void	redir_inp(t_redir_list *redir, int *fd)
{
	*fd = open(redir->filename, O_RDONLY, 0644);
	if ((*fd) != -1)
	{
		dup2(*fd, STDIN_FILENO);
		close(*fd);
	}
}
