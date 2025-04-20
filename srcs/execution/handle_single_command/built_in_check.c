#include "minishell.h"

int	is_on_parent(char *build_in_f, t_command *cmd, t_env *env, t_gc *gc)
{
	if (!ft_strcmp(build_in_f, "cd") || !ft_strcmp(build_in_f, "unset") || (!ft_strcmp(build_in_f, "export") && cmd->cmd[1] != NULL))
	{
		printf("============ run on parent proccess ==================\n");
		if (!ft_strcmp(build_in_f, "cd"))
			return (my_cd(cmd->cmd), 1);
		else if (!ft_strcmp(build_in_f, "unset"))
			return (my_unset(&env, cmd->cmd), 1);
		else if (!ft_strcmp(build_in_f, "export"))
			return (my_export(gc, &env, cmd->cmd), 1);
		// else if (ft_strcmp(build_in_f, "exit"))
		// 	my_exit(cmd->cmd);
	}
	return (0);
}

int	is_on_child(char *build_in_f, t_command *cmd, t_env *env, t_gc *gc)
{
	printf("============ run on child procces ===============\n");
	if (!ft_strcmp(build_in_f, "echo"))
		return (my_echo(cmd->cmd), 1);
	else if (!ft_strcmp(build_in_f, "pwd"))
		return (my_pwd(), 1);
	else if (!ft_strcmp(build_in_f, "export") && cmd->cmd[1] == NULL)
		return (my_export(gc, &env, cmd->cmd), 1);
	else if (!ft_strcmp(build_in_f, "env"))
		return (my_env(env), 1);
	return (0);
}
