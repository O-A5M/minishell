/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:38:40 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/07/04 22:09:27 by oakhmouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/include/execution.h"
#include "libft/libft.h"

char	*read_func(void)
{
	char	*line;

	line = readline("ZimBomBah$ ");
	if (line == NULL)
		endoffile();
	return (line);
}

t_export	*split_env(char **env)
{
	t_export	*ret;
	char		**splits;
	int		i;

	i = 0;
	while (env[i])
	{
		splits = ft_split(env[i], '=');
		add_last(&ret, ft_new_node(splits[0], splits[1]));
		i++;
	}
	return (ret);
}

t_export	*ft_new_node(char *s, char *str)
{
	t_export	*ret;

	ret = malloc(sizeof(t_export));
	if (!ret)
		return (NULL);
	ret->name = s;
	ret->value = str;
	ret->next = NULL;
	return (ret);
}

//This one adds node to the end of the list.
void	add_last(t_export **s, t_export *t)
{
	t_export	*tmp;

	if (!s || !t)
		return ;
	if (!*s)
	{
		(*s) = t;
	}
	else
	{
		tmp = *s;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = t;
	}
}

char	**split_path(t_export *export)
{
	char	**ret;

	while (export)
	{
		if (!ft_strncmp("PATH", export->name, 4))
		{
			ret = ft_split(export->value, ':');
			// if (!ret)
				//exit_status;
			return (ret);
		}
		export = export->next;
	}
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	char				*cl;
	t_cmd				*cmd;
	char				**path;

	(void)ac;
	(void)av;
	path = split_path(split_env(env));
	set_signals(&sa_int, &sa_quit);
	while (1337)
	{
		if (sigaction(SIGINT, &sa_int, NULL) == -1
			|| sigaction(SIGQUIT, &sa_quit, NULL) == -1)
			sigaction_exit();
		cl = read_func();
		add_history(cl);
		cmd = parser(cl);
		start_execution(cmd, env, path);
		free(cl);
	}
	rl_clear_history();
}
