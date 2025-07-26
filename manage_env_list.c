/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:15:37 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/26 22:06:01 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_path(char **env)
{
	char		**ret;
	char		**tmp1;
	char		*tmp2;
	int			index;

	index = 0;
	tmp2 = NULL;
	while (env[index])
	{
		if ((tmp2 = ft_strnstr(env[index], "PATH", 5)))
		{
			tmp1 = ft_split(tmp2, '=');
			ret = ft_split(tmp1[1], ':');
			free_array(tmp1);
			return (ret);
		}
		index++;
	}
	return (NULL);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


char	*ft_getenv(char *name, char **env)
{
	char	*var;
	char	**tmp;

	tmp = __environ;
	__environ = env;
	var = getenv(name);
	__environ = tmp;
	return (var);
}
