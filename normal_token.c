/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:19:40 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/06/02 19:19:41 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	casual_character_found(char *cl, unsigned int *index, t_args **args, t_cmd **pipeline)
{
	t_args	*ptr;
	char	*arg;
	int		arg_is_done;

	ptr = *args;
	arg = get_normal_token(cl, index);
	if (is_whitespace_character(cl[*index + 1])
		|| is_meta_character(cl[*index + 1]))
		arg_is_done = 1;
	else
		arg_is_done = 0;
	append_arg(args, arg, arg_is_done);
}

char	*get_normal_token(char *cl, unsigned int *index)
{
	char			*normal_token;
	unsigned int	start_index;

	start_index = *index;
	while (cl[*index] != '\0' && cl[*index] != '$'
		&& !is_whitespace_character(cl[*index])
		&& !is_meta_character(cl[*index]) && !is_quote_character(cl[*index]))
		*index += 1;
	normal_token = ft_substr(cl, start_index, *index - start_index);
	return (normal_token);
}
