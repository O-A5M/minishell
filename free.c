/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:05:48 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/07/01 12:05:50 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(t_args *args)
{
	t_args	*ptr;
	t_args	*tmp;

	ptr = args;
	while (ptr != NULL)
	{
		tmp = ptr;
		ptr = ptr->next;
		if (tmp->arg != NULL)
		{
			free(tmp->arg);
			tmp->arg = NULL;
		}
		free(tmp);
	}
}

void	free_redirections(t_redir_list *redirections)
{
	t_redir_list	*ptr;
	t_redir_list	*tmp;

	ptr = redirections;
	while (ptr != NULL)
	{
		tmp = ptr;
		ptr = ptr->next;
		if (tmp->filename != NULL)
		{
			free(tmp->filename);
			tmp->filename = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

void	free_double_array(char **arr)
{
	int	i;

	if (arr != NULL)
	{
		i = 0;
		while (arr[i] != NULL)
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

void	free_command(t_cmd **command)
{
	t_cmd	*ptr;
	t_cmd	*tmp;

	ptr = *command;
	while (ptr != NULL)
	{
		tmp = ptr;
		ptr = ptr->next;
		free_args(tmp->args_list);
		free_double_array(tmp->args_array);
		free_redirections(tmp->redirections);
		free(tmp);
	}
	*command = NULL;
}
