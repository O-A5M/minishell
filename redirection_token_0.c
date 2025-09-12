/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_token_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:09:57 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/08/15 21:10:10 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	one_field_ends_with_ifs(char *token)
{
	char	*ifs;
	int		i;

	ifs = " \t\n";
	i = 0;
	while (token && token[i])
		i++;
	if (num_of_fields(token) == 1 && is_in_ifs(token[i - 1], ifs))
		return (1);
	return (0);
}

char	*one_field_spliter(char *token)
{
	char			*ifs;
	char			*split_token;
	unsigned int	i;
	unsigned int	start;

	ifs = " \t\n";
	i = 0;
	while (is_in_ifs(token[i], ifs))
		i++;
	start = i;
	while (token[i] && !is_in_ifs(token[i], ifs))
		i++;
	split_token = ft_substr(token, start, (size_t)(i - start));
	free(token);
	return (split_token);
}

int	other_cases(char *filename, char *token, char *cl, int index)
{
	if ((is_other(cl[index]) || is_a_quote(cl[index]))
		&& one_field_ends_with_ifs(token))
		return (1);
	if ((is_other(cl[index]) || is_a_quote(cl[index]))
		&& filename && all_in_ifs(token))
		return (1);
	if (!filename && all_in_ifs(token) && (cl[index] == '\0'))
		return (1);
	if (!filename && (token[0] == '\0') && (cl[index] == '\0'))
		return (1);
	else
		return (0);
}

int	check_things_out(char *filename, char **token, char *cl, int index)
{
	if (simple_cases(filename, *token))
		return (1);
	else if (other_cases(filename, *token, cl, index))
		return (1);
	else
	{
		if (all_in_ifs(*token))
		{
			free(*token);
			*token = ft_strdup("");
		}
		else if (one_field_starts_with_ifs(*token)
			|| one_field_ends_with_ifs(*token))
			*token = one_field_spliter(*token);
	}
	return (0);
}

char	*extract_filename(char *cl, unsigned int *index,
			int **exp_amb, char **env)
{
	char			*token;
	char			*filename;

	filename = NULL;
	(*exp_amb)[1] = 0;
	while (is_other(cl[*index]) || is_a_quote(cl[*index]) || cl[*index] == '$')
	{
		if (is_a_quote(cl[*index]))
		{
			(*exp_amb)[0] = 0;
			token = get_quoted_token(cl, index, env);
		}
		else if (cl[*index] == '$')
		{
			token = get_expanded_token(cl, index, env);
			if (!((*exp_amb)[1]))
				(*exp_amb)[1] = check_things_out(filename, &token, cl, *index);
		}
		else if (is_other(cl[*index]))
			token = get_normal_token(cl, index);
		filename = add_text(token, filename);
		if (filename == NULL)
			break ;
	}
	return (filename);
}
