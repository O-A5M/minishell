/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:03:26 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/22 16:39:47 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_cmd *cmd)
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
			printf("%s No such file or directory\n", cmd->args_array[1]);
			return (TECHNICAL_ERR);
		}
	}
	else
	{
		user = getenv("HOME");
		if (!(ret = chdir(user)))
			return (SUCCES);
		else
		{
			printf("%s No such file or directory\n", cmd->args_array[1]);
			return (TECHNICAL_ERR);
		}
	}
}
