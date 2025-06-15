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

t_redir_list	*create_redir(t_cmd **head, t_redir_type redir_type,
				char *filename)
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

void	append_redir(t_redir_list **head, t_redir_type redir_type,
		char *filename)
{
	t_redir_list	*ptr;

	if (*head == NULL)
		*head = create_redir(head, redir_type, filename);
	else
	{
		ptr = *head;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = create_redir(redir_type, filename);
	}
}
