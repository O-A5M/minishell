/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakhmouc <oakhmouc@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:56:52 by oakhmouc          #+#    #+#             */
/*   Updated: 2025/07/28 14:31:28 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_cmd **cmd, t_export **export, char ***env)
{
	(void)cmd;
	free_array((*env));
	free_export_list((*export));
	printf("exit\n");
	exit(0);
}
