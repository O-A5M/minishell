/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_functions_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 20:56:16 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/08/15 20:57:22 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**get_fd_close(void)
{
	static int	*fd;

	return (&fd);
}

t_cmd	***get_command(void)
{
	static t_cmd	**command;

	return (&command);
}

t_export	**get_export_list(void)
{
	static t_export	*export;

	return (&export);
}

char	***get_env_array(void)
{
	static char	**env;

	return (&env);
}

int	*get_fd(void)
{
	static int	fd;

	return (&fd);
}
