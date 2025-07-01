#include "../include/execution.h"
#include "../../minishell.h"

void  start_execution(t_cmd *cmd, char **env)
{
	execve(cmd->args_array[0], cmd->args_array, env);
}

