/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built_ins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:02:39 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/26 12:05:37 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_exit(t_cmd *cmd)
{
	printf("hello");
	printf("%s", cmd->args_array[0]);
	return (0);
}

int	handle_built_ins(t_cmd *cmd, char ***env)
{
	char	*tmp;

	tmp = cmd->args_array[0];
	if (!strncmp(tmp, "echo", 5))
		return (ft_echo(cmd));
	else if (!strncmp(tmp, "cd", 3))
		return (ft_cd(cmd, *env));
	else if (!strncmp(tmp, "pwd", 4))
		return (ft_pwd());
	else if (!strncmp(tmp, "export", 7))
		return (ft_export(cmd, env));
	else if (!strncmp(tmp, "unset", 6))
		return (ft_unset(cmd, env));
	else if (!strncmp(tmp, "env", 4))
		return (ft_env(*env));
	else if (!strncmp(tmp, "exit", 5))
		return (ft_exit(cmd));
	else
		return (CMD_N_FOUND);
	return (SUCCES);
}
