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
	struct s_export	*previous;
}				t_export;

//struct for storing the component of the simple command.
typedef struct s_simple_command
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
	//flag for the output 0=(>) and 1=(>>)
	int		out_mode;
}				t_simple_command;

//struct for the pipline type of commands
typedef struct s_pipeline
{
	//the commands between the pipes
	t_simple_command			*command;
	struct s_pipeline			*next;
	struct s_pipeline			*previouse;
}				t_pipeline;

void	set_signals(struct sigaction *sa_int, struct sigaction *sa_quit);
void	parsing(void);
void	sigaction_exit(void);
void	endoffile(void);
char	**tokenizer(char *cl);
void	unclosed_quotes_error(void);
void	after_operator_error(void);

#endif /* MINISHELL_H */
