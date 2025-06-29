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

// void	other_found(char *cl, unsigned int *index,
		// t_args **args, t_cmd **command)
// {
// 	t_args	*ptr;
// 	char	*arg;
// 	int		done_arg;

// 	ptr = *args;
// 	arg = get_normal_token(cl, index);
// 	if (is_a_whitespace(cl[*index + 1])
// 		|| is_meta_character(cl[*index + 1]))
// 		done_arg = 1;
// 	else
// 		done_arg = 0;
// 	append_arg(args, arg, done_arg);
// }
//
char	*get_normal_token(char *cl, unsigned int *index)
{
	char			*normal_token;
	unsigned int	start_index;

	start_index = *index;
	while (is_other(cl[*index]))
		*index += 1;
	normal_token = ft_substr(cl, start_index, *index - start_index);
	return (normal_token);
}
