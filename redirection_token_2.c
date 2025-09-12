/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_token_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:06:52 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/08/13 11:27:23 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	all_in_ifs(char *s)
{
	char	*ifs;
	int		i;

	ifs = " \t\n";
	i = 0;
	if (s[i] == '\0')
		return (0);
	while (is_in_ifs(s[i], ifs))
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

char	*filename_ret(char *filename, int ambi)
{
	if (ambi)
	{
		free(filename);
		return (NULL);
	}
	return (filename);
}

int	num_of_fields(char *token)
{
	char	*ifs;
	int		i;
	int		num;

	ifs = " \t\n";
	i = 0;
	num = 0;
	while (token && token[i])
	{
		while (is_in_ifs(token[i], ifs))
			i++;
		if (token[i])
			num += 1;
		while (token[i] && !is_in_ifs(token[i], ifs))
			i++;
	}
	return (num);
}

int	one_field_starts_with_ifs(char *token)
{
	char	*ifs;

	ifs = " \t\n";
	if (num_of_fields(token) == 1 && is_in_ifs(token[0], ifs))
		return (1);
	return (0);
}
