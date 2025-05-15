/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:31:01 by oakhmouc          #+#    #+#             */
/*   Updated: 2024/11/14 15:14:17 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int			ret;
	long int	nb;

	ret = 0;
	nb = n;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		ret++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		ret++;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	char			*ret;
	int				i;
	long int		nb;

	nb = n;
	i = ft_intlen(n) - 1;
	ret = (char *) malloc(sizeof(char) * (ft_intlen(n) + 1));
	if (ret == NULL)
		return (NULL);
	ret[ft_intlen(n)] = '\0';
	if (nb == 0)
		ret[i] = '0';
	if (nb < 0)
	{
		ret[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		ret[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	return (ret);
}
