#include "../minishell.h"

void	env_command(t_export *list)
{
	while (list)
	{
		printf("%s=%s\n", list->name, list->value);
		list = list->next;
	}
}
