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

//	The expansion case will need to be handled separately
//		as it can only be concluded after making the expansion.
int	quote_found(char *cl, unsigned int *index, t_cmd **cmd_head)
{
	char	*arg;
	int		done_arg;

	arg = get_quoted_token(cl, index);
	if (arg == NULL)
		return (-1);
	if (is_a_pipe(cl[*index]) || is_a_redir(cl[*index])
		|| is_a_whitespace(cl[*index]) || !cl[*index])
		done_arg = 1;
	else
		done_arg = 0;
	append_arg(&(((*cmd_head)->last_node)->args_list), arg, done_arg);
	return (0);
}

int	expansion_found(char *cl, unsigned int *index, t_cmd **cmd_head)
{
	char	*expanded;
	char	*ifs;
	int		done_arg;

	expanded = get_expanded_token(cl, index);
	if (expanded == NULL)
		return (-1);
	ifs = " \t\n";
	done_arg = 0;
	if (is_a_pipe(cl[*index]) || is_a_redir(cl[*index])
		|| is_a_whitespace(cl[*index]) || cl[*index] == '\0')
		done_arg = 1;
	if (!expanded[0])
	{
		(*cmd_head)->last_node->expansion_flag = 1;
		free(expanded);
		if ((*cmd_head)->last_node->args_list &&
			(*cmd_head)->last_node->args_list->arg_is_done == 0)
			(*cmd_head)->last_node->args_list->arg_is_done = done_arg;
		return (0);
	}
	else
		field_split(expanded, ifs, cmd_head, done_arg);
	return (0);
}

// free_args_list();
int	pipe_found(char *cl, unsigned int *index, t_cmd **cmd_head)
{
	*index += 1;
	if ((*cmd_head)->args_array == NULL && (*cmd_head)->args_list == NULL
		&& (*cmd_head)->redirections == NULL && (*cmd_head)->expansion_flag == 0)
	{
		pipe_error();
		return (-1);
	}
	while (is_a_whitespace(cl[*index]))
		*index += 1;
	if (cl[*index] == '\0' || is_a_pipe(cl[*index]))
	{
		pipe_error();
		return (-1);
	}
	(*cmd_head)->last_node->args_array
		= list_to_arr((*cmd_head)->last_node->args_list);
	append_command(cmd_head, NULL, NULL, NULL);
	return (0);
}

// when filename is an empty string, this function treats it
// as a correct filename. would need to treat that when at execution.
int	redir_found(char *cl, unsigned int *index, t_cmd **cmd_head)
{
	t_redir_type	redir_type;
	char			*token;
	char			*filename;

	filename = NULL;
	redir_type = what_redirection_type(cl, index);
	if (redir_type == 13)
		return (-1);
	while (is_other(cl[*index]) || is_a_quote(cl[*index]) || cl[*index] == '$')
	{
		if (is_a_quote(cl[*index]))
			token = get_quoted_token(cl, index);
		else if (cl[*index] == '$')
			token = get_expanded_token(cl, index);
		else if (is_other(cl[*index]))
			token = get_normal_token(cl, index);
		if (token == NULL)
		{
			free(filename);
			return (-1);
		}
		filename = add_text(token, filename);
	}
	append_redir(*cmd_head, redir_type, filename);
	return (0);
}

int	other_found(char *cl, unsigned int *index, t_cmd **cmd_head)
{
	char	*arg;
	int		done_arg;

	arg = get_normal_token(cl, index);
	if (arg == NULL)
		return (-1);
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
	return (0);
}
