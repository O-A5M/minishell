#include "../minishell.h"

// void	env_command(t_export *list)
// {
// 	while (list)
// 	{
// 		printf("%s=%s\n", list->name, list->value);
// 		list = list->next;
// 	}
// }

void	remove_element(t_export *list)
{
}

void	unset_command(char *var, t_export **list)
{
	size_t	len;

	len = ft_strlen(var);
	while ((*list))
	{
		if (!ft_strncmp(var, (*list)->name, len))
		{
			remove_element(*list);
		}
	}
}
