#include "../minishell.h"
#include <stdlib.h>

int	*ft_pipe(void)
{
	int	*fd;

	fd = malloc (sizeof(fd));
	if (!fd)
		exit(1);
	if (pipe(fd) != 0)
		exit (1);
	return (fd);
}
