/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:49:46 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/05/21 10:55:14 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_export
{
	char			*name;
	char			*value;
	struct s_export	*next;
}				t_export;

void	set_signals(struct sigaction *sa_int, struct sigaction *sa_quit);
void	parsing(void);
void	sigaction_exit(void);
void	endoffile(void);

#endif /* MINISHELL_H */
