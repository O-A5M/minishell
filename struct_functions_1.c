/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_functions_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:57:15 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/06/12 09:57:18 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_command(char **args_array, t_args *args_list,
						t_redir_list *redirection_list)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd) * 1);
	if (new == NULL)
		return (NULL);
	new->args_array = args_array;
	new->args_list = args_list;
	new->redirections = redirection_list;
	new->next = NULL;
	return (new);
}

void	append_command(t_cmd **head, char **args_array, t_args *args_list,
						t_redir_list *redirection_list)
{
	t_cmd	*ptr;

	if (*head == NULL)
	{
		*head = create_command(args_array, args_list, redirection_list);
		(*head)->last_node = *head;
	}
	else
	{
		ptr = *head;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = create_command(args_array, args_list, redirection_list);
		(*head)->last_node = ptr->next;
	}
}
