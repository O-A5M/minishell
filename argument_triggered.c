#include "minishell.h"

void	quote_found(char *cl, unsigned int *index, t_args **args, t_cmd **command)
{

}

void	expansion_found(char *cl, unsigned int *index, t_args **args, t_cmd **command)
{

}

void	pipe_found(char *cl, unsigned int *index, t_args **args, t_cmd **command)
{
	char	**args;

	*index += 1;
	if (is_a_pipe(cl[*index]))
		pipe_error();
	args = list_to_arr(*args);
	new_command(command, args);
}

void	redir_found(char *cl, unsigned int *index, t_args **args, t_cmd **command)
{

}

void	other_found(char *cl, unsigned int *index, t_args **args, t_cmd **command)
{
	t_args	*ptr;
	char	*arg;
	int		arg_is_done;

	ptr = *args;
	arg = get_normal_token(cl, index);
	if (is_a_pipe(cl[*index]) || is_a_redir(cl[*index])
		|| is_a_whitespace(cl[*index]))
	{
		arg_is_done = 1;
	}
	else
	//	The expansion case will need to be handled separately
	//		as it can only be concluded after making the expansion.
	{
		arg_is_done = 0;
	}
	append_arg(args, arg, arg_is_done);
}
