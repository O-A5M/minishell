/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:38:40 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/07/27 19:08:25 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	return_status = 0;

char	*read_func(void)
{
	char	*line;

	line = readline("\033[0;32mZimBomBah$ \033[0m");
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
	t_export			*export;

	(void)ac;
	(void)av;
	export = NULL;
	set_signals(&sa_int, &sa_quit);
	arr_to_list(&export, env);
	while (1337)
	{
	if (sigaction(SIGINT, &sa_int, NULL) == -1
			|| sigaction(SIGQUIT, &sa_quit, NULL) == -1)
			sigaction_exit();
		cl = read_func();
		add_history(cl);
		cmd = parser(cl, env_to_arr(export));
		if (cl[0] != '\0')
			return_status = start_execution(cmd, &export);
		free(cl);
	}
	rl_clear_history();
}
