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

t_redir_list	*create_redir(t_redir_type redir_type,
					char *filename, char *literal_filename)
{
	t_redir_list	*new;

	new = malloc(sizeof(t_redir_list) * 1);
	if (new == NULL)
		return (NULL);
	new->redir_type = redir_type;
	new->filename = filename;
	new->literal_filename = literal_filename;
	new->ambiguous_flag = 0;
	new->fd = -1;
	new->heredoc_file = NULL;
	new->next = NULL;
	return (new);
}

void	append_redir(t_cmd *command, t_redir_type redir_type,
			char *filename, char *literal_filename)
{
	t_redir_list	*ptr;
	t_cmd			*last_command;

	last_command = command->last_node;
	if (last_command->redirections == NULL)
	{
		last_command->redirections
			= create_redir(redir_type, filename, literal_filename);
		last_command->redirections->last_node = last_command->redirections;
	}
	else
	{
		ptr = last_command->redirections;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = create_redir(redir_type, filename, literal_filename);
		last_command->redirections->last_node = ptr->next;
	}
}
