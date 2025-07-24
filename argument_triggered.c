/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_triggered.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:39:38 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/07/24 17:42:46 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	The expansion case will need to be handled separately
//		as it can only be concluded after making the expansion.
void	quote_found(char *cl, unsigned int *index,
		t_cmd **cmd_head, char **env)
{
	char	*arg;
	int		done_arg;

	arg = get_quoted_token(cl, index, env);
	if (is_a_pipe(cl[*index]) || is_a_redir(cl[*index])
		|| is_a_whitespace(cl[*index]))
		done_arg = 1;
	else
		done_arg = 0;
	append_arg(&(((*cmd_head)->last_node)->args_list), arg, done_arg);
}

void	expansion_found(char *cl, unsigned int *index,
		t_cmd **cmd_head, char **env)
{
	char	*arg;
	int		done_arg;

	arg = expand_token(cl, index, env);
	if (is_a_pipe(cl[*index]) || is_a_redir(cl[*index])
		|| is_a_whitespace(cl[*index]))
		done_arg = 1;
	else
		done_arg = 0;
	append_arg(&(((*cmd_head)->last_node)->args_list), arg, done_arg);
}

// free_args_list();
void	pipe_found(char *cl, unsigned int *index,
		t_cmd **cmd_head)
{
	*index += 1;
	while (is_a_whitespace(cl[*index]))
		*index += 1;
	if (cl[*index] == '\0' || is_a_pipe(cl[*index]))
		pipe_error();
	(*cmd_head)->last_node->args_array = list_to_arr((*cmd_head)->last_node->args_list);
	append_command(cmd_head, NULL, NULL, NULL);
}

void	redir_found(char *cl, unsigned int *index,
		t_cmd **cmd_head, char **env)
{
	t_redir_type	redir_type;
	char			*filename;

	filename = NULL;
	redir_type = what_redirection_type(cl, index);
	if (is_a_quote(cl[*index]))
		filename = get_quoted_token(cl, index, env);
	else if (is_an_expansion(cl[*index]))
		filename = expand_token(cl, index, env);
	else if (is_other(cl[*index]))
		filename = get_normal_token(cl, index);
	append_redir(*cmd_head, redir_type, filename);
}

void	other_found(char *cl, unsigned int *index,
		t_cmd **cmd_head)
{
	char	*arg;
	int		done_arg;

	arg = get_normal_token(cl, index);
	if (is_a_pipe(cl[*index]) || is_a_redir(cl[*index])
		|| is_a_whitespace(cl[*index]) || cl[*index] == '\0')
	{
		done_arg = 1;
	}
	else
	{
		done_arg = 0;
	}
	append_arg(&(((*cmd_head)->last_node)->args_list), arg, done_arg);
}
