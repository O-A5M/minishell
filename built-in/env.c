/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:44:12 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/28 15:44:14 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **env)
{
	int	index;

	index = 0;
	while (env[index])
	{
		if (ft_strchr(env[index], '='))
			printf("%s\n", env[index]);
		index++;
	}
	return (SUCCES);
}
