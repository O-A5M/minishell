/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:56:52 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/08/17 00:23:22 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <limits.h>
#include <unistd.h>

static int	check_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (2);
		i++;
	}
	return (0);
}

static int	is_overflow(long long num, int digit, int sign)
{
	if (sign == 1 && (num > (LLONG_MAX - digit) / 10))
		return (1);
	if (sign == -1 && (-num < (LLONG_MIN + digit) / 10))
		return (1);
	return (0);
}

static int	ft_str_to_exitcode(const char *nptr, long long *ret)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		if (is_overflow(result, nptr[i] - 48, sign))
			return (1);
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	*ret = result * sign;
	return (0);
}

static void	free_all(t_cmd *cmd, t_export **export, char ***env, char **path)
{
	int		*i;

	(void) cmd;
	i = NULL;
	if (!(*(*get_command()))->next)
	{
		i = (*get_fd_close());
		close(i[0]);
		close(i[1]);
		free_command((*get_command()));
		(*(*get_command())) = NULL;
	}
	else if ((*(*get_command())) && (*(*get_command()))->next)
		free_command((*get_command()));
	free_array(path);
	free_array((*env));
	free_export_list((*export));
	rl_clear_history();
}

int	ft_exit(t_cmd **cmd, t_export **export, char ***env, char **path)
{
	long long	ret;

	printf("exit\n");
	if ((*cmd)->args_array[1])
	{
		if (check_number((*cmd)->args_array[1]) != 0
			|| ft_str_to_exitcode((*cmd)->args_array[1], &ret))
		{
			ft_putstr_fd((*cmd)->args_array[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			ret = 2;
		}
		else if ((*cmd)->args_array[2])
		{
			g_return_status = 1;
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (g_return_status);
		}
	}
	else
		ret = g_return_status;
	ret = (unsigned char)ret;
	free_all(*cmd, export, env, path);
	exit(ret);
	return (0);
}
