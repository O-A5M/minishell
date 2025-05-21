/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:38:40 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/04/22 19:47:40 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_func(void)
{
	char	*line;

	line = readline("ZimBomBah$ ");
	if (line == NULL)
		endoffile();
	add_history(line);
	free(line);
	return (line);
}

void	parsing(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	char				*read_line;

	set_signals(&sa_int, &sa_quit);
	while (1337)
	{
		if (sigaction(SIGINT, &sa_int, NULL) == -1
			|| sigaction(SIGQUIT, &sa_quit, NULL) == -1)
			sigaction_exit();
		read_line = read_func();
	}
}
