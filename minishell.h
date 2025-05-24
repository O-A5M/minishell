/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:49:46 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/05/21 10:55:14 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_export
{
	char			*name;
	char			*value;
	struct s_export	*next;
}				t_export;

typedef struct	s_simple_command
{
	//which command should be executed.
	char	*command_name;
	//command arguments like -l, -rf, etc...
	char	**args;
	//variables assinged to the command line.
	char	**var_assign;
	//input redirection (<)
	char	*red_in;
	//output redirection (>>, >)
	char	*red_out;
	//flag for the input 0=> and 1=>>
	int		out_mode;
}				t_simple_command;

void	set_signals(struct sigaction *sa_int, struct sigaction *sa_quit);
void	parsing(void);
void	sigaction_exit(void);
void	endoffile(void);

#endif /* MINISHELL_H */
