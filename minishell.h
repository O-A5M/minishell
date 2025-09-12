/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:49:46 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/17 00:03:07 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//	The necessary library includes to our unique minishell project.
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# define SUCCES 0
# define TECHNICAL_ERR 1
# define CMD_N_FOUND 127

extern int						g_return_status;
// extern volatile sig_atomic_t	g_child_sig;

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
	char				*literal_filename;
	t_redir_type		redir_type;
	int					fd;
	int					ambiguous_flag;
	char				*heredoc_file;
	struct s_redir_list	*last_node;
	struct s_redir_list	*next;
}				t_redir_list;

//	List that contains nodes, each node with `arg` where a single token
//	is stored, and a flag that determines if the arg is complete yet or not.
typedef struct s_args
{
	char			*arg;
	int				arg_is_done;
	struct s_args	*last_node;
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

// this list has all the necessary elements for the pipeline
typedef struct s_pipe_ctx
{
	int			fd[2];
	int			prev_fd;
	pid_t		pid;
	t_cmd		*cmd;
	char		**env;
	char		**path;
	t_export	**export;
}				t_pipe_ctx;

//	All the necessary function prototypes for our unique minishell project.
char			*read_func(t_cmd **command, t_export *export);
t_cmd			*parser(char *cl, char **env);
void			setup_main(struct sigaction *sa_int, struct sigaction *sa_quit,
					t_cmd **command, t_export **export);
void			handle_signal(int signum);
void			sigaction_exit(t_cmd **command);
void			endoffile(t_cmd **command, t_export *export);
int				is_a_whitespace(char c);
int				is_a_pipe(char c);
int				is_a_redir(char c);
t_redir_type	what_redirection_type(char *cl, unsigned int *index);
int				is_an_expansion(char c);
int				is_a_quote(char c);
int				is_other(char c);
int				quote_found(char *cl, unsigned int *index,
					t_cmd **command, char **env);
int				pipe_found(char *cl, unsigned int *index,
					t_cmd **command);
int				redir_found(char *cl, unsigned int *index,
					t_cmd **command, char **env);
int				expansion_found(char *cl, unsigned int *index,
					t_cmd **command, char **env);
int				other_found(char *cl, unsigned int *index,
					t_cmd **command);
char			*get_normal_token(char *cl, unsigned int *index);
char			*add_text(char *text_chunk, char *dst);
char			*valid_token_expansion(char *cl, unsigned int *index,
					char **env);
char			*get_expanded_token(char *cl, unsigned int *index,
					char **env);
char			*expand_quoted_text(char *quoted_text, char **env);
char			*get_quoted_token(char *cl, unsigned int *index,
					char **env);
void			pipe_error(void);
t_cmd			*create_command(char **args_array, t_args *args_list,
					t_redir_list *redirection_list);
void			append_command(t_cmd **head, char **args_array,
					t_args *args_list, t_redir_list *redirection_list);
t_args			*create_arg(char *arg, int done_arg);
void			append_arg(t_args **head, char *arg, int done_arg);
size_t			list_len(t_args *args);
char			**list_to_arr(t_args *args);
t_redir_list	*create_redir(t_redir_type redir_type,
					char *filename, char *literal_filename);
void			append_redir(t_cmd *command, t_redir_type redir_type,
					char *filename, char *literal_filename);
void			unclosed_quotes_error(void);
void			redirection_error(char c);
void			free_args(t_args *args);
void			free_redirections(t_redir_list *redirections);
void			free_double_array(char **arr);
void			free_command(t_cmd **command);
char			*my_split(char *expanded, char *ifs, int *index,
					t_cmd **command);
int				field_split(char *expanded, char *ifs,
					t_cmd **command, int done_arg);
int				is_in_ifs(char c, char *s);
char			*extract_filename(char *cl, unsigned int *index,
					int **expand, char **env);
int				heredoc_found(t_cmd **command, int **exp_amb, char **env);
int				open_error(void);
int				fork_error(void);
void			heredoc_eof_warning(char *dlmtr);
t_cmd			***get_command(void);
void			setup_heredoc_signal(t_cmd **command);
void			ignore_parent_signal(t_cmd **command);
int				all_in_ifs(char *s);
char			*filename_ret(char *filename, int ambi);
int				num_of_fields(char *token);
int				one_field_starts_with_ifs(char *token);
int				simple_cases(char *filename, char *token);
t_export		**get_export_list(void);
char			***get_env_array(void);
int				*get_fd(void);
char			*remove_quotes(char *delimiter);

// Execution part
int				start_execution(t_cmd *cmd, t_export **expot);
char			*get_path(char *cmd, char **path);
t_export		*ft_new_node(char *s, char *str);
void			add_last(t_export **s, t_export *t);
int				find_command(char **path, char *s);
void			free_env(t_export **expot);
char			**split_path(char **m_env);
void			free_array(char	**arr);
t_export		*split_env(char **env);
int				simple_command(t_cmd *cmd, char **env, char **path,
					t_export **expot);
t_export		*set_env(char **env);
char			**envdup(char **env, char *var);
char			*search_command(t_cmd *cmd, char **path);
int				pipe_line(t_cmd *cmd, char **env, char **path,
					t_export **expot);
int				redirection_case_pipe(t_cmd *cmd, char **env,
					char **path, t_export **expot);
int				ft_cd(t_cmd *cmd, char **env);
int				handle_built_ins(t_cmd *cmd, char ***env, t_export **expot,
					char **path);
int				ft_echo(t_cmd *cmd);
int				ft_pwd(void);
int				ft_export(t_cmd *cmd, t_export **expot);
int				ft_unset(t_cmd *cmd, t_export **expot);
int				ft_env(char **env);
char			*ft_getenv(char *name, char **env);
int				cd_check(t_cmd *cmd, char **env);
int				handle_fd(t_redir_list *redir);
int				arr_to_list(t_export **head, char **env);
t_export		*new_node(char *name, char *value);
void			add_one_node(t_export *news, t_export **head);
char			**env_to_arr(t_export *expot);
char			**splitenv(char *env);
void			reset_signal(int flag);
void			free_export_list(t_export *head);
int				ft_exit(t_cmd **cmd, t_export **expot, char ***env,
					char **path);
int				is_directory(char *path);
void			dir_message(t_cmd *cmd, char **env, char *cmd_ret);
void			restore_fd(int fd1, int fd2);
int				wait_child(pid_t pid);
void			child_work_pipe(int prev_fd, int *fd, t_cmd *cmd);
void			parent_work(int	*prev_fd, int *fd, t_cmd *cmd);
int				**get_fd_close(void);
void			redir_out(t_redir_list *redir, int *fd);
void			redir_inp(t_redir_list *redir, int *fd);
void			redir_app(t_redir_list *redir, int *fd);

#endif /* MINISHELL_H */
