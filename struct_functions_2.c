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

void	append_arg(t_args **args_head, char *arg, int done_arg)
{
	t_args	*ptr;
	char	*tmp;

	if (*args_head == NULL)
	{
		*args_head = create_arg(arg, done_arg);
	}
	else
	{
		ptr = *args_head;
		while (ptr->next != NULL)
			ptr = ptr->next;
		if (ptr->arg_is_done == 0)
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
	t_args	*ptr;

	len = list_len(args);
	arr = malloc(sizeof(char *) * (len + 1));
	if (arr == NULL)
		return (NULL);
	index = 0;
	ptr = args;
	while (ptr)
	{
		arr[index] = ft_strdup(ptr->arg);
		index += 1;
		ptr = ptr->next;
	}
	arr[index] = NULL;
	return (arr);
}
