/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:03:26 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/08/13 11:58:41 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

static int	home_cd(t_cmd *cmd, char **env)
{
	char	*user;
	int		ret;

	(void) cmd;
	ret = 0;
	user = ft_getenv("HOME", env);
	if (!user)
	{
		ft_putstr_fd("HOME not set\n", 2);
		return (TECHNICAL_ERR);
	}
	if (!ft_strncmp(user, "\0", 1))
		return (SUCCES);
	ret = chdir(user);
	if (!ret)
		return (SUCCES);
	else
	{
		perror("Error");
		return (TECHNICAL_ERR);
	}
}

int	ft_cd(t_cmd *cmd, char **env)
{
	int		ret;

	ret = 0;
	if (cmd->args_array[1])
	{
		ret = chdir(cmd->args_array[1]);
		if (!ret)
		{
			return (TECHNICAL_ERR);
		}
		else
		{
			perror("Error");
			return (TECHNICAL_ERR);
		}
	}
	else
		return (home_cd(cmd, env));
}
