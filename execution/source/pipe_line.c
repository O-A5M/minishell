/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:53:10 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/08/18 04:04:21 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <unistd.h>

static int	exit_msg(int status, t_pipe_ctx *ctx, t_cmd *cmd)
{
	g_return_status = status;
	if (status == CMD_N_FOUND)
	{
		ft_putstr_fd(cmd->args_array[0], 2);
		ft_putstr_fd(": Command not found\n", 2);
		free_command(&(ctx->cmd));
		free_array(ctx->env);
		free_export_list(*(ctx->export));
		exit (g_return_status);
	}
	else
	{
		free_command(&(ctx->cmd));
		free_export_list(*(ctx->export));
		free_array(ctx->env);
		exit (g_return_status);
	}
}

static int	wait_child_pipe(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	return (status);
}

static void	exec_child_process(t_pipe_ctx *ctx, t_cmd *tmp)
{
	reset_signal(1);
	child_work_pipe(ctx->prev_fd, ctx->fd, tmp);
	exit_msg(redirection_case_pipe(tmp, ctx->env, ctx->path, ctx->export),
		ctx, tmp);
}

static int	pipe_line_loop(t_pipe_ctx *ctx)
{
	t_cmd	*tmp;

	tmp = ctx->cmd;
	while (tmp)
	{
		if ((tmp->next) && pipe(ctx->fd) == -1)
			return (TECHNICAL_ERR);
		ctx->pid = fork();
		if (ctx->pid == -1)
			return (TECHNICAL_ERR);
		else if (ctx->pid == 0)
			exec_child_process(ctx, tmp);
		parent_work(&ctx->prev_fd, ctx->fd, tmp);
		tmp = tmp->next;
	}
	return (g_return_status);
}

int	pipe_line(t_cmd *cmd, char **env, char **path, t_export **export)
{
	t_pipe_ctx	ctx;
	int			status;

	ctx.prev_fd = -1;
	(*get_command()) = &cmd;
	ctx.cmd = cmd;
	ctx.env = env;
	ctx.path = path;
	ctx.export = export;
	reset_signal(0);
	if (pipe_line_loop(&ctx) == TECHNICAL_ERR)
		return (TECHNICAL_ERR);
	while (waitpid(ctx.pid, &status, 0) > 0)
		g_return_status = wait_child_pipe(status);
	return (g_return_status);
}
