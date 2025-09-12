/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_triggered.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:39:38 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/16 23:33:28 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	The expansion case will need to be handled separately
//		as it can only be concluded after making the expansion.
int	quote_found(char *cl, unsigned int *index, t_cmd **command, char **env)
{
	char	*arg;
	int		done_arg;

	arg = get_quoted_token(cl, index, env);
	if (arg == NULL)
		return (-1);
	if (is_a_pipe(cl[*index]) || is_a_redir(cl[*index])
		|| is_a_whitespace(cl[*index]) || !cl[*index])
		done_arg = 1;
	else
		done_arg = 0;
	append_arg(&(((*command)->last_node)->args_list), arg, done_arg);
	return (0);
}

int	expansion_found(char *cl, unsigned int *index, t_cmd **command, char **env)
{
	char	*expanded;
	char	*ifs;
	int		done_arg;
	int		ret;

	expanded = get_expanded_token(cl, index, env);
	if (expanded == NULL)
		return (-1);
	(*command)->last_node->expansion_flag = 1;
	ifs = " \t\n";
	done_arg = 0;
	if (is_a_pipe(cl[*index]) || is_a_redir(cl[*index])
		|| is_a_whitespace(cl[*index]) || cl[*index] == '\0')
		done_arg = 1;
	if (!expanded[0])
	{
		free(expanded);
		if ((*command)->last_node->args_list && done_arg == 1)
			(*command)->last_node->args_list->last_node->arg_is_done = 1;
		ret = 0;
	}
	else
		ret = field_split(expanded, ifs, command, done_arg);
	return (ret);
}

// free_args_list();
int	pipe_found(char *cl, unsigned int *index, t_cmd **command)
{
	*index += 1;
	if (!((*command)->args_array) && !((*command)->args_list)
		&& !((*command)->redirections) && !((*command)->expansion_flag))
	{
		g_return_status = 2;
		pipe_error();
		return (-1);
	}
	while (is_a_whitespace(cl[*index]))
		*index += 1;
	if (!(cl[*index]) || is_a_pipe(cl[*index]))
	{
		g_return_status = 2;
		pipe_error();
		return (-1);
	}
	(*command)->last_node->args_array
		= list_to_arr((*command)->last_node->args_list);
	append_command(command, NULL, NULL, NULL);
	return (0);
}

int	redir_found(char *cl, unsigned int *index, t_cmd **command, char **env)
{
	t_redir_type	redir_type;
	char			*literal_filename;
	char			*filename;
	unsigned int	start;
	int				*exp_amb;

	redir_type = what_redirection_type(cl, index);
	exp_amb = malloc(sizeof(int) * 2);
	exp_amb[0] = 1;
	start = *index;
	filename = extract_filename(cl, index, &exp_amb, env);
	literal_filename = ft_substr(cl, start, (size_t)(*index - start));
	if (redir_type == 13 || !filename || !literal_filename)
		return (free(filename), free(literal_filename), free(exp_amb), -1);
	append_redir(*command, redir_type, filename, literal_filename);
	(*command)->last_node->redirections->last_node->ambiguous_flag = exp_amb[1];
	if (redir_type == HEREDOC)
	{
		g_return_status = heredoc_found(command, &exp_amb, env);
		return (!!g_return_status * (-2));
	}
	free(exp_amb);
	return (0);
}

int	other_found(char *cl, unsigned int *index, t_cmd **command)
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
	append_arg(&(((*command)->last_node)->args_list), arg, done_arg);
	return (0);
}
