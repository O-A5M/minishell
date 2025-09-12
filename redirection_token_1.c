/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_token_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:26:45 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/08/15 20:40:46 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Called to read from the user and store in heredoc file.
void	heredoc_loop(t_cmd **command, int fd, int expand, char **env)
{
	char	*readd;
	char	*dlmtr;

	dlmtr = (*command)->last_node->redirections->last_node->literal_filename;
	dlmtr = remove_quotes(dlmtr);
	(*command)->last_node->redirections->last_node->literal_filename = dlmtr;
	while (42)
	{
		readd = readline("> ");
		if (readd == NULL || !ft_strncmp(readd, dlmtr, ft_strlen(dlmtr) + 1))
			break ;
		if (expand)
			readd = expand_quoted_text(readd, env);
		write(fd, readd, ft_strlen(readd));
		write(fd, "\n", 1);
		free(readd);
		readd = NULL;
	}
	if (readd == NULL)
		heredoc_eof_warning(dlmtr);
	free(readd);
}

// Called When Inside Child Process Created for Heredoc, Reads into Heredoc File
int	heredoc_child(t_cmd **command, int expand, char **env)
{
	char	*heredoc_file;
	int		fd;

	heredoc_file = (*command)->last_node->redirections->last_node->heredoc_file;
	fd = open(heredoc_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (open_error());
	*get_fd() = fd;
	heredoc_loop(command, fd, expand, env);
	close(fd);
	free_command(command);
	free_export_list(*get_export_list());
	free_array(*get_env_array());
	return (0);
}

// Called To Start Operating on Heredoc
int	heredoc_operate(t_cmd **command, int **exp_amb, char **env)
{
	pid_t				pid;
	int					status;
	int					ret;
	int					expand;

	expand = (*exp_amb)[0];
	free(*exp_amb);
	(*exp_amb) = NULL;
	pid = fork();
	if (pid == 0)
	{
		*get_command() = command;
		setup_heredoc_signal(command);
		ret = heredoc_child(command, expand, env);
		exit(ret);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
		else
			return (WEXITSTATUS(status));
	}
	return (fork_error());
}

// Called When Heredoc is Spotted
int	heredoc_found(t_cmd **command, int **exp_amb, char **env)
{
	static int			id;
	char				*heredoc_file;
	int					ret;
	int					fd;
	char				*count;

	ignore_parent_signal(command);
	count = ft_itoa(id);
	heredoc_file = ft_strjoin("/tmp/.mshd", count);
	free(count);
	(*command)->last_node->redirections->last_node->heredoc_file = heredoc_file;
	id++;
	ret = heredoc_operate(command, exp_amb, env);
	if (ret != 0)
		return (ret);
	fd = open(heredoc_file, O_RDONLY);
	if (fd < 0)
		return (open_error());
	unlink(heredoc_file);
	(*command)->last_node->redirections->last_node->fd = fd;
	return (ret);
}
