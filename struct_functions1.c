/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_functions1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:02:50 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/06/04 15:02:52 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_command(char **args)
{
	t_cmd	*ptr;

	ptr = malloc(sizeof(t_cmd) * 1);
	if (ptr == NULL)
		return (NULL);
	ptr->args = args;
	ptr->is_built_in = 0;
	ptr->input_type = STDIN;
	ptr->infile = NULL;
	ptr->output_type = STDOUT;
	ptr->outfile = NULL;
	ptr->next = NULL;
}

void	append_command(t_cmd **head, char **args)
{
	t_cmd	*ptr;

	if (*head == NULL)
	{
		*head = new_command(args);
	}
	else
	{
		ptr = *head;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = new_command(args);
	}
}
