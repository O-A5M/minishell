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

t_cmd	*create_command(char **args)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd) * 1);
	if (new == NULL)
		return (NULL);
	new->args = NULL;
	new->next = NULL;
	return (new);
}

void	new_command(t_cmd **head, char **args)
{
	t_cmd	*ptr;

	if (*head == NULL)
		*head = create_command(args);
	else
	{
		ptr = *head;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = create_command(args);
	}
}
