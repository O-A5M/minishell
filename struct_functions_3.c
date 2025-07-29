/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_functions_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:57:15 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/06/15 23:59:16 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_heredoc(t_redir_type redir_type, char *filename, int expand)
{
	static int	id;
	char		*readd;
	int			fd;

	if (redir_type != HEREDOC)
		return 0;
	fd = open(ft_strjoin("/tmp/.mshd", ft_itoa(id)), O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("Couldn't Open File For Here-doc!\n");
		return (-1);
	}
	id++;
	while ((readd = readline("> ")) != NULL && ft_strncmp(readd, filename, ft_strlen(filename) + 1))
	{
		if (expand)
			readd = expand_quoted_text(readd);
		write(fd, readd, ft_strlen(readd));
		write(fd, "\n", 1);
		// read;
	}
	close(fd);
	return (0);
}

t_redir_list	*create_redir(t_redir_type redir_type, char *filename)
{
	t_redir_list	*new;

	new = malloc(sizeof(t_redir_list) * 1);
	if (new == NULL)
		return (NULL);
	new->redir_type = redir_type;
	new->filename = filename;
	new->next = NULL;
	return (new);
}

void	append_redir(t_cmd *cmd_head, t_redir_type redir_type,
		char *filename)
{
	t_redir_list	*ptr;
	t_cmd			*last_command;

	last_command = cmd_head->last_node;
	if (last_command->redirections == NULL)
		last_command->redirections = create_redir(redir_type, filename);
	else
	{
		ptr = last_command->redirections;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = create_redir(redir_type, filename);
	}
}
