/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:21:10 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/06/02 17:21:12 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotes_found(char *cl, unsigned int *index, t_args **args, t_cmd **pipeline)
{
	t_args	*ptr;
	char	*arg;
	int		arg_is_done;

	ptr = *args;
	arg = get_quoted_token(cl, index);
	if (is_whitespace_character(cl[*index + 1])
		|| is_meta_character(cl[*index + 1]))
		arg_is_done = 1;
	else
		arg_is_done = 0;
	append_arg(args, arg, arg_is_done);
}

char	*get_quoted_token(char *cl, unsigned int *index)
{
	unsigned int	start_index;
	char			*quoted_text;
	char			quote_sign;

	quote_sign = cl[*index];
	*index += 1;
	start_index = (unsigned int)*index;
	while (cl[*index] != '\0' && cl[*index] != quote_sign)
		*index += 1;
	if (cl[*index] == '\0')
		unclosed_quotes_error();
	quoted_text = ft_substr(cl, start_index, *index - start_index);
	*index += 1;
	if (quote_sign == '"')
		quoted_text = quoted_text_expander(quoted_text);
	return (quoted_text);
}
