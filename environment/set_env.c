/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:15:46 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/24 16:02:52 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**envdup(char **env, char *var)
{
	int		len;
	char	**ret;

	len = 0;
	while (env[len])
		len++;
	if (var)
		len++;
	ret = malloc((len + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	len = 0;
	while (env[len])
	{
		ret[len] = ft_strdup(env[len]);
		len++;
	}
	if (var)
	{
		ret[len] = ft_strdup(var);
		len++;
	}
	ret[len] = NULL;
	return (ret);
}
