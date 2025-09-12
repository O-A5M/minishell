/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:47:09 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/08/13 12:13:41 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

int	ft_strchr_rev(char *s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

static void	print_arg(t_cmd *cmd, int i)
{
	int	index;

	index = i;
	while (cmd->args_array[index])
	{
		printf("%s", cmd->args_array[index]);
		if (cmd->args_array[index + 1] != NULL)
			printf(" ");
		index++;
	}
}

int	ft_echo(t_cmd *cmd)
{
	int	index;
	int	nl;

	index = 1;
	nl = 0;
	if (!cmd->args_array[1])
	{
		write(1, "\n", 1);
		return (SUCCES);
	}
	while (cmd->args_array[index]
		&& !ft_strncmp(cmd->args_array[index], "-n", 2))
	{
		if (ft_strchr_rev(cmd->args_array[index]))
			break ;
		index++;
		nl = 1;
	}
	print_arg(cmd, index);
	if (nl == 0)
		printf("\n");
	return (SUCCES);
}
