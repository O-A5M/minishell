/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:12:15 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/05/24 12:12:19 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_tokens(char *cl)
{
	int		index;
	t_args	*args;
	t_cmd	*pipeline;

	index = 0;
	args = NULL;
	pipeline = NULL;
	while (cl[index] != '\0')
	{
		while (is_a_whitespace(cl[index]))
			index += 1;
		if (cl[index] == '\'' || cl[index] == '"')
			quotes_found(cl, &index, &args, &pipeline);
			// get_quoted_token(cl, &index, pipeline, &args);
		if (cl[index] == '|' || cl[index] == '>' || cl[index] == '<')
			meta_token_found(cl, &index, &args, &pipeline);
			// get_meta_token(cl, &index, pipeline);
		if (cl[index] == '$')
			get_expanded_token(cl, &index, pipeline, &args);
		if	(cl[index] != '\0' && cl[index] != '$'
			&& !is_a_whitespace(cl[index])
			&& !is_quote_character(cl[index]) && !is_meta_character(cl[index]))
			casual_character_found(cl, &index, &args, &pipeline);
			// get_normal_token(cl, &index, pipeline, &args);
	}
}

char	**tokenizer(char *cl)
{
	t_cmd	*pipeline_head;
	char	*word;

	pipeline_head = new_command();
	get_tokens(cl, &pipeline_head);
	return (tokens);
}
