/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:38:40 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/07/24 17:33:51 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char	*read_func(void)
{
	char	*line;

	line = readline("ZimBomBah$ ");
	if (line == NULL)
		endoffile();
	return (line);
}

int	main(int ac, char **av, char **env)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	char				*cl;
	t_cmd				*cmd;
	char				**m_env;

	(void)ac;
	(void)av;
	set_signals(&sa_int, &sa_quit);
	m_env = envdup(env, NULL);
	while (1337)
	{
	if (sigaction(SIGINT, &sa_int, NULL) == -1
			|| sigaction(SIGQUIT, &sa_quit, NULL) == -1)
			sigaction_exit();
		cl = read_func();
		add_history(cl);
		cmd = parser(cl, m_env);
		start_execution(cmd, &m_env);
		free(cl);
	}
	rl_clear_history();
}
