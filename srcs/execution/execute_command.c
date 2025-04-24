#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void execute_command(t_gc *gc, t_command *cmd, t_env *env)
{
	int cmd_size = 0;

	cmd_size = ft_cmdsize(cmd);
	if (cmd_size > 1)
	{
		printf("handle multiple command\n");
		handle_multiple_command(gc, cmd, env);
	}
	else
	{
		printf("hanldle single command\n");
		handle_single_command(gc, cmd, env);
	}
}