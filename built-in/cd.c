#include "../minishell.h"

void	cd(char	*dir)
{
	int	ret;

	ret = chdir(dir);
	if (ret != 0);
		return ;
}
