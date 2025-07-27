#include "../minishell.h"

int	ft_pwd(void)
{
	char	s[4096];

	printf("%s\n", getcwd(s, 4096));
	return (SUCCES);
}
