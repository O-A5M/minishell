#include "../minishell.h"

void	pwd(void)
{
	char	s[4096];

	printf("%s", getcwd(s, 4096));
}
