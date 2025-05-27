#include "../minishell.h"
#include <stddef.h>



void	unset_command(t_export **list, char *var)
{
	t_export	*tmp;
	size_t		len;

	tmp = NULL;
	len = ft_strlen(var);
	while (*list)
	{
		if (!ft_strncmp(var, (*list)->name, len))
		{
			tmp = (*list)->previous;
			tmp->next = (*list)->next;
			tmp = (*list)->next;
			tmp->previous = (*list)->previous;
			free(*list);
			return ;
		}
		else
			(*list) = (*list)->next;
	}
}
