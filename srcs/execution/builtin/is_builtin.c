#include "minishell.h"

char *is_builtin (char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return ("echo");
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return ("cd");
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return ("pwd");
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return ("export");
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return ("unset");
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return ("env");
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return ("exit");
	else
		return (NULL);
}

int	is_builtin_excute(t_gc *gc, t_env **env, t_command *cmd)
{
	if (ft_strncmp(*cmd->cmd, "echo", 4) == 0)
		return (my_echo(cmd->cmd), 1);
	else if (ft_strncmp(*cmd->cmd, "cd", 2) == 0)
		return (my_cd(cmd->cmd), 1);
	else if (ft_strncmp(*cmd->cmd, "pwd", 3) == 0)
		return (my_pwd(), 1);
	else if (ft_strncmp(*cmd->cmd, "export", 6) == 0)
		return (my_export(gc, env, cmd->cmd), 1);
	else if (ft_strncmp(*cmd->cmd, "unset", 5) == 0)
		return (my_unset(env, cmd->cmd), 1);
	else if (ft_strncmp(*cmd->cmd, "env", 3) == 0)
		return (my_env(*env), 1);
	// else if (ft_strncmp(cmd, "exit", 4) == 0)
	// 	return (my_exit(), 1);
	else
		return (0);
}
