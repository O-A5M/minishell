/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:03:26 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/24 18:32:26 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_cmd *cmd,char **env)
{
	int		ret;
	char	*user;

	ret = 0;
	if (cmd->args_array[1])
	{
		if (!(ret = chdir(cmd->args_array[1])))
			return (SUCCES);
		else
		{
			ft_putstr_fd(cmd->args_array[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (TECHNICAL_ERR);
		}
	}
	else
	{
		user = ft_getenv("HOME", env);
		if (!ft_strncmp(user, "\0", 1))
			return (SUCCES);
		if (!(ret = chdir(user)))
			return (SUCCES);
		else
		{
			ft_putstr_fd(cmd->args_array[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (TECHNICAL_ERR);
		}
	}
}
