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

int	is_a_whitespace(char c)
{
	if (a == ' ' || a >= 9 && a <= 13)
		return (1);
	else
		return (0);
}

int	is_quote_character(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	else
		return (0);
}

/*
	would have been fun but some will take time, it
	will be inconvenient  to do some and not others

/*int	is_a_special_variable(char c)
{
	if ((c >= '0' && c <= '9') || c == '#' || c == '?'
		|| c == '$' || c == '-' || c == '*' || c == '@'
		|| c == '_' || c == '!')
		return (1);
}

void	print_special_variable(char c)
{

}*/

void	print_exit_status(int *index)
{
	int	exit_status;

	exit_status = 0;
	*index += 1;
	printf("%d\n", exit_status);
}

void	get_meta_token(char *cl, int *idx, t_cmd **pipeline)
{
	
}

void	get_normal_token(char *cl, int *idx, t_cmd **pipeline, t_args **args)
{
	// You traverse, find the whole word, get it into a char *word.
	// Then if you were stopped by a quote character or a `$` sign
	//  you call the suitable function to get it, you get it in
	//  another char *word, and you join it with the 1st word.
	// And you keep going. Sounds like a great plan!
	while (cl[*idx] && cl[*idx] != '\'' && cl[*idx] != '"'
		&& cl[*idx] != '|' && cl[*idx] != '>' && cl[*idx] != '<'
		&& cl[*idx] != ' ' && !(cl[*idx] >= 9 && cl[*idx] <= 13))
	{
		if (cl[*idx] == '$')
			;
		else

	}
}

void	join_and_clean(char **result, char *pre_expansion, char *expanded_token)
{
	*result = ft_strjoin(*result, pre_expansion);
	if (*result == NULL)
		allocation_error();
	*result = ft_strjoin(*result, expanded_token);
	if (*result == NULL)
		allocation_error();
	free(pre_expansion);
	free(expanded_token);
}

char	*get_expanded_token(char *cl, int *index/*, t_cmd **pipeline, t_args **args*/)
{
	char			*expanded_token;
	unsigned int	start_index;
	int				exit_status;

	*index += 1;
	start_index = *index;
	if (is_a_whitespace(cl[*index]) || cl[*index] == '\0')
		return (ft_strdup("$"));
	else if (is_quote_character(cl[*index]))
		return (ft_strdup(""));
	else if (cl[*index] == '?')
	{
		*index += 1;
		exit_status = 127;
		return (ft_itoa(exit_status));
	}
	else if (is_a_valid_character(cl[*index]))
	{

	}

char	*extract_expansions(char *quoted_text)
{
	char			*pre_expansion;
	char			*expanded_token;
	char			*result;
	int				index;
	unsigned int	start;

	result = NULL;
	index = 0;
	while (quoted_text[index])
	{
		start = (unsigned int)index;
		while (quoted_text[index] && quoted_text[index] != '$')
			index++;
		if (quoted_text[index])
		{
			if (!result)
				result = "";
			pre_expansion = ft_substr(quoted_text, start, index - start);
			expanded_token = get_expanded_token(quoted_text, &index);
			join_and_clean(&result, pre_expansion, expanded_token);
		}
	}
	if (!result)
		return (quoted_text);
	free(quoted_text);
	return (result);
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
	if (quote_character == '"')
		quoted_text = extract_expansions(quoted_text);
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
		while (is_a_whitespace(cl[idx]))
			idx++;
		if (cl[idx] == '\'' || cl[idx] == '"')
			get_quoted_token(cl, &idx, pipeline, &args);
		if (cl[idx] == '|' || cl[idx] == '>' || cl[idx] == '<')
			get_meta_token(cl, &idx, pipeline);
		if (cl[idx] == '$')
			get_expanded_token(cl, &idx, pipeline, &args);
		if (cl[idx] != '\'' && cl[idx] != '"' && cl[idx] != '|'
			&& cl[idx] != '>' && cl[idx] != '<' && cl[idx] != '$'
			&& !(is_a_whitespace(cl[idx])))
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
