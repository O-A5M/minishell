/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:53:50 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/07/24 17:42:46 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_all(t_cmd *command)
{
	int	cmd_counter;
	int	i;

	cmd_counter = 0;
	while (command != NULL)
	{
		cmd_counter += 1;
		i = 0;
		if (command->args_array)
		{
			printf("ARGS:\n");
			while (command->args_array[i] != NULL)
			{
				printf("[%s]\n", command->args_array[i]);
				i += 1;
			}
		}
		printf("\nREDIRECTIONS:\n");
		while (command->redirections != NULL)
		{
			if (command->redirections->redir_type == 0)
				printf("[REDIRECTION OUT]: %s\n", command->redirections->filename);
			else if (command->redirections->redir_type == 1)
				printf("[APPEND]: %s\n", command->redirections->filename);
			else if (command->redirections->redir_type == 2)
				printf("[REDIRECTION IN]: %s\n", command->redirections->filename);
			else if (command->redirections->redir_type == 3)
				printf("[HEREDOC]: %s\n", command->redirections->filename);
			else
				printf("ERROR!!!\n");
			command->redirections = command->redirections->next;
		}
		printf("\n");
		printf("	Command n%d is complete\n", cmd_counter);
		command = command->next;
	}
}

t_cmd	*parser(char *cl, char **env)
{
	t_cmd			*command;
	unsigned int	index;

	command = NULL;
	append_command(&command, NULL, NULL, NULL);
	index = 0;
	while (cl[index])
	{
		while (is_a_whitespace(cl[index]))
			index += 1;
		if (is_other(cl[index]))
			other_found(cl, &index, &command);
		if (is_a_quote(cl[index]))
			quote_found(cl, &index, &command, env);
		if (is_an_expansion(cl[index]))
			expansion_found(cl, &index, &command, env);
		if (is_a_pipe(cl[index]))
			pipe_found(cl, &index, &command);
		if (is_a_redir(cl[index]))
			redir_found(cl, &index, &command, env);
	}
	(command->last_node)->args_array
		= list_to_arr((command->last_node)->args_list);
	// print_all(command);
	return (command);
}
