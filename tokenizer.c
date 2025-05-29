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

/*void	operator_token(char **cl, size_t *ct)
{
	char	redir;

	if (**cl == '|')
	{
		*cl += 1;
	}
	else
	{
		redir = **cl;
		*cl += 1;
		if (**cl == redir)
			*cl += 1;
	}
	if (**cl == '\0')
		after_operator_error();
	*ct += 1;
}

void	quote_token(char **cl)
{
	char	qt;

	qt = **cl;
	*cl += 1;
	while (**cl && **cl != qt)
	{
		*cl += 1;
	}
	if (**cl != qt)
		unclosed_quotes_error();
	*cl += 1;
}

void	check_flag(char *flag, size_t *ct)
{
	if (*flag)
		*ct += 1;
	*flag = 0;
}

size_t	count_tokens(char *cl)
{
	char	flag;
	size_t	ct;

	flag = 0;
	ct = 0;
	while (*cl)
	{
		while (*cl == ' ' || (*cl >= 9 && *cl <= 13))
			cl++;
		while (*cl && *cl != '>' && *cl != '<' && *cl != '|'
			&& !(*cl >= 9 && *cl <= 13) && *cl != ' ')
		{
			flag = 1;
			if (*cl == '\'' || *cl == '"')
				quote_token(&cl);
			else
				cl++;
		}
		check_flag(&flag, &ct);
		if (*cl == '|' || *cl == '>' || *cl == '<')
			operator_token(&cl, &ct);
	}
	return (ct);
}
*/

void	get_expanded_token(char *cl, int *idx, t_cmd **pipeline, t_args **args)
{

}

void	get_meta_token(char *cl, int *idx, t_cmd **pipeline)
{
	
}

void	get_normal_token(char *cl, int *idx, t_cmd **pipeline, t_args **args)
{
	
}

char	*get_quoted_token(char *cl, int *index, t_cmd **pipeline, t_args **args)
{
	unsigned int	start_index;
	char			*quoted_text;
	char			quote_character;

	quote_character = cl[*index];
	*index += 1;
	start_index = (unsigned int)*index;
	while (cl[*index] != '\0' && cl[*index] != quote_character)
	*index += 1;
	if (cl[*index] == '\0')
	unclosed_quotes_error();
	quoted_text = ft_substr(cl, start_index, (size_t)*index - (size_t)start_index);
	*index += 1;
	append_arg(args, quoted_text);
	return (quoted_text);
}

void	get_tokens(char *cl, t_cmd **pipeline_head)
{
	int		idx;
	t_cmd	*pipeline;
	t_args	*args;

	idx = 0;
	args = NULL;
	while (cl[idx])
	{
		while (cl[idx] == ' ' || (cl[idx] >= 9 && cl[idx] <= 13))
			idx++;
		if (cl[idx] == '\'' || cl[idx] == '"')
			get_quoted_token(cl, &idx, pipeline, &args);
		if (cl[idx] == '|' || cl[idx] == '>' || cl[idx] == '<')
			get_meta_token(cl, &idx, pipeline);
		if (cl[idx] == '$')
			get_expanded_token(cl, &idx, pipeline, &args);
		if (cl[idx] != '\'' && cl[idx] != '"' && cl[idx] != '|'
			&& cl[idx] != '>' && cl[idx] != '<' && cl[idx] != '$'
			&& cl[idx] != ' ' && !(cl[idx] >= 9 && cl[idx] <= 13))
			get_normal_token(cl, &idx, pipeline, &args);
	}
}

char	**tokenizer(char *cl)
{
	t_cmd	*pipeline_head;
	char	*word;

	pipeline_head = new_command();
	get_tokens(cl, &pipeline_head);
	// while (*cl)
	// {
	// 	// word = get_next_token(cl, &index);
	// 	insert_token(&pipeline, word);
	// }
	// tokens = NULL;
	// len = count_tokens(cl);
	// printf("You have %d tokens.\n", (int)len);
	// tokens = malloc(sizeof(char *) * (len + 1));
	// if (!tokens)
	// 	return (NULL);

	return (tokens);
}
