/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:38:22 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/05/07 12:02:28 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[])
{
	(void)av;
	if (isatty(STDIN_FILENO) && ac == 1)
	{
		parsing();
		rl_clear_history();
	}
}
