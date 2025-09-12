/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:43:53 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/08/13 12:07:22 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

int	ft_pwd(void)
{
	char	s[4096];
	char	*p;

	p = getcwd(s, 4096);
	if (!p)
		perror("Error");
	else
		printf("%s\n", s);
	return (SUCCES);
}
