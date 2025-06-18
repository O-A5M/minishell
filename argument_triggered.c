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
		t_cmd **cmd_head)
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
	append_arg(&(*cmd_head)->last_node->args_list, arg, done_arg);
}

void	expansion_found(char *cl, unsigned int *index,
		t_cmd **cmd_head)
{
	// char	**split_arg;
	char	*arg;
	int		done_arg;
	// int		i;
	int		limits;

	arg = expand_token(cl, index);
	if (is_a_pipe(cl[*index]) || is_a_redir(cl[*index])
		|| is_a_whitespace(cl[*index]))
		done_arg = 1;
	//	The expansion case will need to be handled separately
	//		as it can only be concluded after making the expansion.
	else
		done_arg = 0;
	// split_arg = expansion_field_split(arg, " \t\n");
	// i = 0;
	// if ()
	// while (split_arg[i] != NULL)
	// {
		// if (split_arg[i + 1] == NULL)
			// append_arg(args, split_arg[i], done_arg);
		// else
			// append_arg(args, split_arg[i], 1);
		// i += 1;
	// }
	append_arg(&(*cmd_head)->last_node->args_list, arg, done_arg);
}

void	pipe_found(char *cl, unsigned int *index,
		t_cmd **cmd_head)
{
	t_cmd	*ptr;
	char	**args_arr;
	int		done_arg;

	*index += 1;
	while (is_a_whitespace(cl[*index]))
		*index += 1;
	if (cl[*index] == '\0' || is_a_pipe(cl[*index]))
		pipe_error();
	(*cmd_head)->last_node->args_array = list_to_arr((*cmd_head)->args_list);
	append_command(cmd_head, NULL, NULL, NULL);
	// (*cmd_head)->last_node->redirections = ;
	// ptr = *cmd_head;
	// while (ptr != NULL)
	// 	ptr = ptr->next;
	// (*cmd_head)->
	// args_arr = list_to_arr(*args);
	// append_cmd_head(cmd_head, args_arr);
}

void	redir_found(char *cl, unsigned int *index,
		t_cmd **cmd_head)
{
	t_redir_type	redir_type;
	// typedef struct s_redir_list
	// {
	// 	char				*file;
	// 	t_redir_type		redir;
	// 	struct s_redir_list	*next;
	// }				t_redir_list;
	redir_type = what_redirection_type(cl, index);
	append_redir(cmd_head, redir_type, "LOL");
	// append_arg(&(*cmd_head)->last_node->args_list, arg, done_arg);


}

void	other_found(char *cl, unsigned int *index,
		t_cmd **cmd_head)
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
	append_arg(&(*cmd_head)->last_node->args_list, arg, done_arg);
}
