/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_triggered.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:39:38 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/06/16 00:39:40 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_found(char *cl, unsigned int *index,
		t_args **args, t_cmd **command)
{
	char	*arg;
	int		done_arg;

	arg = get_quoted_token(cl, index);
	if (is_a_pipe(cl[*index]) || is_a_redir(cl[*index])
		|| is_a_whitespace(cl[*index]))
		done_arg = 1;
	//	The expansion case will need to be handled separately
	//		as it can only be concluded after making the expansion.
	else
		done_arg = 0;
	append_arg(args, arg, done_arg);
}

void	expansion_found(char *cl, unsigned int *index,
		t_args **args, t_cmd **command)
{
	char	*arg;
	int		done_arg;

	arg = expand_token(cl, index);
	if (is_a_pipe(cl[*index]) || is_a_redir(cl[*index])
		|| is_a_whitespace(cl[*index]))
		done_arg = 1;
	//	The expansion case will need to be handled separately
	//		as it can only be concluded after making the expansion.
	else
		done_arg = 0;
	append_arg(args, arg, done_arg);
}

void	pipe_found(char *cl, unsigned int *index,
		t_args **args, t_cmd **command)
{
	char	**args_arr;

	*index += 1;
	while (is_a_whitespace(cl[*index]))
		*index += 1;
	if (cl[*index] == '\0' || is_a_pipe(cl[*index]))
		pipe_error();
	args_arr = list_to_arr(*args);
	append_command(command, args_arr, );
}

void	redir_found(char *cl, unsigned int *index,
		t_args **args, t_cmd **command)
{
	// typedef struct s_redir_list
	// {
	// 	char				*file;
	// 	t_redir_type		redir;
	// 	struct s_redir_list	*next;
	// }				t_redir_list;
	if (cl[*index] == '>' && cl[*index + 1] == '>')
	{

	}
	else if (cl[*index] == '<' && cl[*index + 1] == '<')
	{

	}
	else if (cl[*index] == '>' && cl[*index + 1] == '>')
	{

	}
	else if (cl[*index] == '>' && cl[*index + 1] == '>')
	{

	}
	else
	{

	}
	append_redir(command, );
	append_arg();


}

void	other_found(char *cl, unsigned int *index,
		t_args **args, t_cmd **command)
{
	char	*arg;
	int		done_arg;

	arg = get_normal_token(cl, index);
	if (is_a_pipe(cl[*index]) || is_a_redir(cl[*index])
		|| is_a_whitespace(cl[*index]))
	{
		done_arg = 1;
	}
	else
	//	The expansion case will need to be handled separately
	//		as it can only be concluded after making the expansion.
	{
		done_arg = 0;
	}
	append_arg(args, arg, done_arg);
}
