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

//	The necessary library includes to our unique minishell project.
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

//	List that for every node, contains the variable name in `name`,
//	along with the corresponding value stored in `value`.
typedef struct s_export
{
	char			*name;
	char			*value;
	struct s_export	*next;
	struct s_export	*previous;
}				t_export;

//	Enum type of data that conatins all the possible redirection types,
//	going from Out Redirection and Append, to In Redirection and HEREDOC.
typedef enum e_redir_type
{
	REDIR_OUT,
	APPEND,
	REDIR_IN,
	HEREDOC,
}			t_redir_type;

//	List that contains nodes, each node with a redirection type,
//	along with a redirection target.
typedef struct s_redir_list
{
	char				*filename;
	t_redir_type		redir_type;
	struct s_redir_list	*next;
}				t_redir_list;

//	List that contains nodes, each node with `arg` where a single token
//	is stored, and a flag that determines if the arg is complete yet or not.
typedef struct s_args
{
	char			*arg;
	int				arg_is_done;
	struct s_args	*next;
}				t_args;

//	List that contains nodes, each node with the command array `args`,
//	and the redirection occurences list in `redirections`.
typedef struct s_cmd
{
	char			**args_array;
	t_args			*args_list;
	int				expansion_flag;
	t_redir_list	*redirections;
	struct s_cmd	*last_node;
	struct s_cmd	*next;
}			t_cmd;

//	All the necessary function prototypes for our unique minishell project.
char			*read_func(t_cmd **command);
t_cmd			*parser(char *cl);
void			set_signals(struct sigaction *sa_int,
					struct sigaction *sa_quit);
void			handle_signal(int signum);
void			sigaction_exit(void);
void			endoffile(t_cmd **command);
int				is_a_whitespace(char c);
int				is_a_pipe(char c);
int				is_a_redir(char c);
t_redir_type	what_redirection_type(char *cl, unsigned int *index);
int				is_an_expansion(char c);
int				is_a_quote(char c);
int				is_other(char c);
int				quote_found(char *cl, unsigned int *index, t_cmd **command);
int				pipe_found(char *cl, unsigned int *index, t_cmd **command);
int				redir_found(char *cl, unsigned int *index, t_cmd **command);
int				expansion_found(char *cl, unsigned int *index, t_cmd **command);
int				other_found(char *cl, unsigned int *index, t_cmd **command);
char			*get_normal_token(char *cl, unsigned int *index);
char			*add_text(char *text_chunk, char *dst);
char			*valid_token_expansion(char *cl, unsigned int *index);
char			*get_expanded_token(char *cl, unsigned int *index);
char			*expand_quoted_text(char *quoted_text);
char			*get_quoted_token(char *cl, unsigned int *index);
void			pipe_error(void);
void			allocation_error(void);
t_cmd			*create_command(char **args_array, t_args *args_list,
					t_redir_list *redirection_list);
void			append_command(t_cmd **head, char **args_array,
					t_args *args_list, t_redir_list *redirection_list);
t_args			*create_arg(char *arg, int done_arg);
void			append_arg(t_args **head, char *arg, int done_arg);
size_t			list_len(t_args *args);
char			**list_to_arr(t_args *args);
// void			free_args(t_args *args);
t_redir_list	*create_redir(t_redir_type redir_type, char *filename);
void			append_redir(t_cmd *cmd_head, t_redir_type redir_type,
					char *filename);

void			unclosed_quotes_error(void);
void			redirection_error(char c);

void			free_args(t_args *args);
void			free_redirections(t_redir_list *redirections);
void			free_double_array(char **arr);
void			free_command(t_cmd **command);

char				*my_split(char *expanded, char *ifs, int *index,
					t_cmd **cmd_head);
int				field_split(char *expanded, char *ifs,
					t_cmd **cmd_head, int done_arg);
int				is_in_ifs(char c, char *s);

#endif /* MINISHELL_H */
