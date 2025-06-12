/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:02:57 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/06/04 15:02:59 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*new_arg(char *arg)
{
	t_args	*ptr;

	ptr = malloc(sizeof(t_args) * 1);
	if (ptr == NULL)
		return (NULL);
	ptr->arg = arg;
	ptr->arg_is_done = 0;
	ptr->next = NULL;
}

void	append_arg(t_args **head, char *arg, int is_arg_done)
{
	t_args	*ptr;
	char	*old_arg;

	if (*head == NULL)
		*head = new_arg(arg);
	else
	{
		ptr = *head;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		if (ptr->arg_is_done == 0)
		{
			old_arg = ptr->arg;
			ptr->arg = ft_strjoin(old_arg, arg);
			free(old_arg);
			free(arg);
			ptr->arg_is_done = is_arg_done;
		}
		else
		{
			ptr->next = new_arg(arg);
		}
	}
}

size_t	list_len(t_args *args)
{
	size_t	len;

	len = 0;
	while (args != NULL)
	{
		len += 1;
		args = args->next;
	}
	return (len);
}

char	**list_to_arr(t_args **head)
{
	char	**arr;
	t_args	*ptr;
	size_t	len;
	int		index;

	ptr = *head;
	len = list_len(*head);
	arr = malloc(sizeof(char *) * (len + 1));
	if (arr == NULL)
		return (NULL);
	index = 0;
	while (ptr)
	{
		*head = (*head)->next;
		arr[index] = ptr->arg;
		index += 1;
		free(ptr);
		ptr = *head;
	}
	arr[index] = NULL;
	free(head);
	head = NULL;
	return (arr);
}
