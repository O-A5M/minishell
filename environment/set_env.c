/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:15:46 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/26 21:53:08 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**envdup(char **env, char *var)
{
	int		len;
	int		index;
	char	**ret;

	len = 0;
	index = 0;
	while (env[len])
		len++;
	if (var)
		len++;
	ret = malloc((len + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (env[index])
	{
		ret[index] = ft_strdup(env[index]);
		index++;
	}
	if (var)
	{
		ret[index] = ft_strdup(var);
		index++;
	}
	ret[index] = NULL;
	return (ret);
}
