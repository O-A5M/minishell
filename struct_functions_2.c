/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_functions_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:57:26 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/06/12 09:57:29 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*create_arg(char *arg, int done_arg)
{
	t_args	*new;

	new = malloc(sizeof(t_args) * 1);
	if (new == NULL)
		return (NULL);
	new->arg = arg;
	new->arg_is_done = done_arg;
	new->next = NULL;
	return (new);
}

// void	new_arg(t_args **head, char *arg, int done_arg)
// {
// 	t_args	*ptr;

// 	if (*head == NULL)
// 		*head = create_arg(arg, done_arg);
// 	else
// 	{
// 		ptr = *head;
// 		while (ptr->next != NULL)
// 			ptr = ptr->next;
// 		ptr->next = create_arg(arg, done_arg);
// 	}
// }

void	append_arg(t_args **head, char *arg, int done_arg)
{
	t_args	*ptr;
	char	*tmp;

	if (*head == NULL)
		*head = create_arg(arg, done_arg);
	else
	{
		ptr = *head;
		while (ptr->next != NULL)
			ptr = ptr->next;
		if (ptr->arg_is_done = 0)
		{
			tmp = ptr->arg;
			ptr->arg = ft_strjoin(ptr->arg, arg);
			ptr->arg_is_done = done_arg;
			free(tmp);
			free(arg);
		}
		else
		{
			ptr->next = create_arg(arg, done_arg);
		}
	}
}

size_t	list_len(t_args *args)
{
	size_t	amount;

	amount = 0;
	while (args != NULL)
	{
		amount += 1;
		args = args->next;
	}
	return (amount);
}

char	**list_to_arr(t_args *args)
{
	char	**arr;
	size_t	len;
	int		index;

	len = list_len(args);
	arr = malloc(sizeof(char *) * (len + 1));
	if (arr == NULL)
		return (NULL);
	index = 0;
	while (args)
	{
		arr[index] = args->arg;
		index += 1;
		args = args->next;
	}
	arr[index] = NULL;
	free_args(args);
	return (arr);
}

void	free_args(t_args *args)
{
	t_args	*ptr;

	ptr = args;
	while (ptr != NULL)
	{
		args = args->next;
		free(ptr);
		ptr = args;
	}
}
