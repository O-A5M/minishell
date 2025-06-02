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

t_cmd	*new_command(char **args)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (node == NULL)
		allocation_error();
	node->args = args;
	node->is_built_in = 0;
	node->input_type = STDIN;
	node->infile = NULL;
	node->output_type = STDOUT;
	node->outfile = NULL;
	node->next = NULL;
	return (node);
}

void	append_command(t_cmd **head, char **args)
{
	t_cmd	*ptr;

	ptr = *head;
	if (*head == NULL)
		*head = new_command(args);
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new_command(args);
	}
}

t_args	*new_arg(char *arg)
{
	t_args	*new;

	new = malloc(sizeof(t_args));
	if (new == NULL)
		allocation_error();
	new->arg = arg;
	new->arg_is_done = 0;
	new->next = NULL;
	return (new);
}

void	append_arg(char *arg, t_args **head, int arg_is_done)
{
	t_args	*ptr;
	char	*old_arg;

	ptr = *head;
	if (*head == NULL)
		*head = new_arg(arg);
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		if (ptr->arg_is_done == 1)
		{
			ptr->next = new_arg(arg);
		}
		else
		{
			old_arg = ptr->arg;
			ptr->arg = ft_strjoin(ptr->arg, arg);
			free(old_arg);
			free(arg);
			if (arg_is_done)
				ptr->arg_is_done = 1;
		}
	}
}
