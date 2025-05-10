/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:39:12 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/04/22 19:47:25 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>

typedef struct s_command
{
	char				*command;
	struct s_command	*next;
}						t_command;

typedef struct	s_export
{
	char			*name;
	char			*value;
	struct s_export	*next;
}				t_export;


#endif /* MINISHELL_H */
