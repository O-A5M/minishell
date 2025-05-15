/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:57:17 by oakhmouc          #+#    #+#             */
/*   Updated: 2024/11/12 14:54:09 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int				i;
	unsigned char	*d;
	unsigned char	*s;

	if (!src && !dst)
		return (NULL);
	if (src > dst)
		return (ft_memcpy(dst, src, n));
	i = n - 1;
	d = (unsigned char *)dst + i;
	s = (unsigned char *)src + i;
	while (i >= 0)
	{
		*d = *s;
		d--;
		s--;
		i--;
	}
	return (dst);
}
