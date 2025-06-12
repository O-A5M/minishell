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

typedef enum e_input
{
	STDIN,
	PIPE_IN,
	REDIR_IN,
	HEREDOC
}			t_input;

typedef enum e_output
{
	STDOUT,
	PIPE_OUT,
	REDIR_OUT,
	APPEND
}			t_output;

typedef struct s_cmd
{
	char			**args;
	int				is_built_in;
	t_input			input_type;
	char			*infile;
	t_output		output_type;
	char			*outfile;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_args
{
	char	*arg;
	int		arg_is_done;
	struct s_args *next;
}				t_args;

//struct for the pipline type of commands
/*typedef struct s_pipeline
{
	//the commands between the pipes
	t_simple_command			*command;
	struct s_pipeline			*next;
	struct s_pipeline			*previouse;
}				t_pipeline;
*/
// void	endoffile(void);
// char	**tokenizer(char *cl);
// void	unclosed_quotes_error(void);
// void	after_operator_error(void);
// t_cmd	*new_node(void);
// void	allocation_error(void);
// char	*get_next_token(char *cl, int *index);
// void	insert_token(t_cmd *pipeline, char *word);
// char	*ft_substr(char const *s, unsigned int start, size_t len);

// t_cmd	*new_command(char **args);
// void	append_command(t_cmd **head, char **args);
// t_args	*new_arg(char *arg);
// void	append_arg(t_args **head, char *arg, int done_arg);
// int	is_a_whitespace(char c);
// int	is_a_pipe(char c);
// int	is_a_redirection(char c);
// int	is_an_expansion(char c);

// void	parsing(void);

char	*read_func(void);
int		parser(char *cl);
void	set_signals(struct sigaction *sa_int, struct sigaction *sa_quit);
void	handle_signal(int signum);
void	sigaction_exit(void);
void	endoffile(void);
int		is_a_whitespace(char c);
int		is_a_pipe(char c);
int		is_a_redir(char c);
int		is_an_expansion(char c);
int		is_a_quote(char c);
int		is_other(char c);
void	quote_found(char *cl, unsigned int *index, t_args **args, t_cmd **command);
void	pipe_found(char *cl, unsigned int *index, t_args **args, t_cmd **command);
void	redir_found(char *cl, unsigned int *index, t_args **args, t_cmd **command);
void	expansion_found(char *cl, unsigned int *index, t_args **args, t_cmd **command);
void	other_found(char *cl, unsigned int *index, t_args **args, t_cmd **command);
char	*get_normal_token(char *cl, unsigned int *index);
void	pipe_error(void);
void	allocation_error(void);
t_cmd	*create_command(char **args);
void	new_command(t_cmd **head, char **args);
t_args	*create_arg(char *arg, int done_arg);
void	append_arg(t_args **head, char *arg, int done_arg);
size_t	list_len(t_args *args);
char	**list_to_arr(t_args *args);
void	free_args(t_args *args);

#endif /* MINISHELL_H */
