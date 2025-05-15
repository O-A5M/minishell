/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:41:12 by oakhmouc          #+#    #+#             */
/*   Updated: 2024/11/13 17:41:14 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cntwrd(const char *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			len++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (len);
}

static int	f_ree(char **s, size_t a)
{
	size_t	i;

	i = 0;
	while (i < a - 1)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (0);
}

static int	m_alloc(char **s, const char *d, char c)
{
	size_t	a;
	size_t	start;
	size_t	i;

	a = 0;
	start = 0;
	i = 0;
	while (d[a])
	{
		while (d[a] == c)
			a++;
		if (!d[a])
			break ;
		start = a;
		while (d[a] && d[a] != c)
			a++;
		s[i] = ft_substr(d, start, a - start);
		if (!s[i++])
			return (f_ree(s, i));
	}
	s[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		len;
	char	**ret;

	if (!s)
		return (NULL);
	len = cntwrd(s, c);
	ret = (char **)malloc((len + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	if (m_alloc(ret, s, c) == 0)
	{
		return (NULL);
	}
	return (ret);
}
