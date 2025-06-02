/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:36:53 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/06/02 19:36:55 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	meta_token_found(char *cl, int *index, t_args **args, t_cmd **pipeline)
{
	// t_args	*ptr;
	// char	*arg;
	// int		arg_is_done;

	// ptr = *args;
	// arg = get_meta_token(cl, index);
	// if (is_whitespace_character(cl[*index + 1])
	// 	|| is_meta_character(cl[*index + 1]))
	// 	arg_is_done = 1;
	// else
	// 	arg_is_done = 0;
	// append_arg(args, arg, arg_is_done);



	// Redirections VS PIPE:

	// ** PIPE  will create a new  command node ** BOTH
	// ** REDIR will create a new argument node **

	// BOTH need to be followed by another token //

	// ** PIPE  will be looking for a command token
	// ** REDIR will be looking for  a  file  token
}

char	*get_meta_token(char *cl, int *index)
{
	char	*meta_token;

	if (cl[*index] == '>')
	{
		if (cl[*index + 1] == '>')
		{
			*index += 1;
			meta_token = ft_strdup(">>");
		}
		else
			meta_token = ft_strdup(">");
	}
	else if (cl[*index] == '<')
	{
		if (cl[*index + 1] == '<')
		{
			*index += 1;
			meta_token = ft_strdup("<<");
		}
		else
			meta_token = ft_strdup("<");
	}
	else
		meta_token = ft_strdup("|");
	*index += 1;
	return (meta_token);
}
