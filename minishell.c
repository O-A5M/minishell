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

char	*read_func(t_cmd **command)
{
	char	*line;

	line = readline("ZimBomBah$ ");
	if (line == NULL)
	{
		endoffile(command);
	}
	return (line);
}

int	main(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	t_cmd				*command;
	char				*cl;

	command = NULL;
	set_signals(&sa_int, &sa_quit);
	while (1337)
	{
		if (sigaction(SIGINT, &sa_int, NULL) == -1
			|| sigaction(SIGQUIT, &sa_quit, NULL) == -1)
			sigaction_exit();
		cl = read_func(&command);
		add_history(cl);
		command = parser(cl);
		if (command != NULL)
		{
			// print_all(command);
			// execute(command);
			free_command(&command);
		}
		free(cl);
	}
	rl_clear_history();
}
