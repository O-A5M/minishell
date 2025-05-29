/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:44:51 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/05/28 13:44:55 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_command(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		allocation_error();
	node->args = NULL;
	node->is_built_in = 0;
	node->input_type = NONE;
	node->infile = NULL;
	node->output_type = NONE;
	node->outfile = NULL;
	node->next = NULL;
	return (node);
}

t_args	*new_arg(char *arg)
{
	t_args	*new;

	new = malloc(sizeof(t_args));
	if (!new)
		allocation_error();
	new->arg = arg;
	new->next = NULL;
	return (new);
}

void	*append_arg(t_args **head, char *arg)
{
	t_args	*ptr;

	ptr = *head;
	if (!(*head))
	{
		*head = new_arg(arg);
		if (!(*head))
			allocation_error();
	}
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_arg(arg);
	}
}
