/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:38:22 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/05/07 12:02:28 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[])
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	char				*line;

	(void)av;
	if (isatty(STDIN_FILENO) && ac == 1)
	{
		set_signals(&sa_int, &sa_quit);
		while (1337)
		{
			if (sigaction(SIGINT, &sa_int, NULL) == -1
				|| sigaction(SIGQUIT, &sa_quit, NULL) == -1)
			{
				perror("Sigaction failed: ");
				exit(1);
			}
			line = readline("ZimBomBah\% ");
			if (line == NULL)
			{
				printf("exit\n");
				break ;
			}
			add_history(line);
			free(line);
		}
		rl_clear_history();
	}
}
