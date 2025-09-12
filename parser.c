/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:53:50 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/08/15 12:59:00 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(t_cmd **command, unsigned int *index, int *ret)
{
	*command = create_command(NULL, NULL, NULL);
	*index = 0;
	*ret = 0;
}

t_cmd	*command_error(int ret, t_cmd **command, char **env)
{
	if (ret == -1 || ret == -2)
	{
		free_command(command);
		*command = NULL;
		if (ret == -1)
			g_return_status = 2;
	}
	else
		(*command)->last_node->args_array
			= list_to_arr((*command)->last_node->args_list);
	free_array(env);
	return (*command);
}

t_cmd	*parser(char *cl, char **env)
{
	t_cmd			*command;
	unsigned int	index;
	int				ret;

	*get_env_array() = env;
	init_vars(&command, &index, &ret);
	while (cl[index])
	{
		while (is_a_whitespace(cl[index]))
			index += 1;
		if (is_other(cl[index]))
			ret = other_found(cl, &index, &command);
		else if (is_a_quote(cl[index]))
			ret = quote_found(cl, &index, &command, env);
		else if (is_an_expansion(cl[index]))
			ret = expansion_found(cl, &index, &command, env);
		else if (is_a_pipe(cl[index]))
			ret = pipe_found(cl, &index, &command);
		else if (is_a_redir(cl[index]))
			ret = redir_found(cl, &index, &command, env);
		if (ret == -1 || ret == -2)
			break ;
	}
	return (command_error(ret, &command, env));
}
