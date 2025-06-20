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

void	read_func(void)
{
	char	*line;

	line = readline("ZimBomBah$ ");
	if (line == NULL)
		endoffile();
	add_history(line);
	tokenizer(line);
	free(line);
	return ;
}

void	parsing(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	set_signals(&sa_int, &sa_quit);
	while (1337)
	{
		if (sigaction(SIGINT, &sa_int, NULL) == -1
			|| sigaction(SIGQUIT, &sa_quit, NULL) == -1)
			sigaction_exit();
		read_func();
	}
}
