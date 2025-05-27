/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:05:34 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/05/25 13:05:37 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Will have to pay attention for allocated memory */
void	unclosed_quotes_error(void)
{
	printf("Parsing Error: Missing Quote Closing Character\n");
	exit(1);
}

void	after_operator_error(void)
{
	printf("Parsing Error: Missing Token After Operator\n");
	exit(1);
}
