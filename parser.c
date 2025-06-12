/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:03:06 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/06/04 15:03:07 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(char *cl)
{
	t_cmd			*command;
	t_args			*args;
	unsigned int	index;

	command = new_command(NULL);
	args = new_arg(NULL);
	index = 0;
	while (cl[index])
	{
		while (is_a_whitespace(cl[index]))
			index += 1;
		if (is_a_quote(cl[index]))
			quote_found(cl, &index, &args, &command);
		if (is_an_expansion(cl[index]))
			expansion_found(cl, &index, &args, &command);
		if (is_a_pipe(cl[index]))
			pipe_found(cl, &index, &args, &command);
		if (is_a_redir(cl[index]))
			redir_found(cl, &index, &args, &command);
		if (is_other(cl[index]))
			other_found(cl, &index, &args, &command);
	}
}
