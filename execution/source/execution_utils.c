/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:07:13 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/18 18:33:34 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_command(char **path, char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (path[i])
	{
		str = ft_strjoin(path[i], s);
		if (access(str, X_OK) == 0)
		{
			free (str);
			return (i);
		}
		free (str);
		i++;
	}
	return (-1);
}

