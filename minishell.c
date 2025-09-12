/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:38:40 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/15 21:13:38 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						g_return_status = 0;

char	*read_func(t_cmd **command, t_export *export)
{
	char	*line;

	line = readline("ZimBomBah$ ");
	if (line == NULL)
		endoffile(command, export);
	return (line);
}

static void	start_command(t_export *export, t_cmd **command,
				struct sigaction sa_int, struct sigaction sa_quit)
{
	char				*cl;

	if (sigaction(SIGINT, &sa_int, NULL) == -1
		|| sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		sigaction_exit(command);
	cl = read_func(command, export);
	if (cl && cl[0] != '\0')
		add_history(cl);
	(*command) = parser(cl, env_to_arr(export));
	if ((*command) != NULL)
		g_return_status = start_execution(*command, &export);
	free_command(command);
	free(cl);
}

int	main(int ac, char **av, char **env)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	t_cmd				*command;
	t_export			*export;

	(void)av;
	(void)ac;
	setup_main(&sa_int, &sa_quit, &command, &export);
	arr_to_list(&export, env);
	while (1337)
		start_command(export, &command, sa_int, sa_quit);
	free_export_list(export);
	rl_clear_history();
	return (0);
}
