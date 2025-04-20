#include "minishell.h"

int	excute_single_command(t_gc *gc, t_command *cmd, t_env **env)
{
	char	**cmd_args;
	char	*cmd_path;
	char	**env_array;

	cmd_args = cmd->cmd;
	if (!cmd_args)
		return (0);
	cmd_path = configure_path(gc, *cmd->cmd, *env);
	if (!cmd_path)
		return (0);
	env_array = convert_env_to_array(gc, *env);
	if (!env_array)
		return ( 0);
	if (execve(cmd_path, cmd_args, env_array) == -1)
		return (printf("Error: EXECVE => (first child)"), 0);
	return (1);
}

void handle_single_command(t_gc *gc, t_command *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*build_in_f;
	int		out_file;
	int	org_stdin = dup(STDIN_FILENO);
	int org_stdout = dup(STDOUT_FILENO);

	if (cmd->cmd[0] == NULL)
		return ;
	build_in_f = is_builtin(*cmd->cmd);
	if (is_on_parent(build_in_f, cmd, env, gc) == 0)
	{
		pid = fork();
		if (pid == -1)
			return (perror("For Error :"));
		if (pid == 0)
		{
			out_file = handle_redirections_single(cmd);
			if (out_file == -1)
				exit(1);
			if (is_on_child(build_in_f, cmd, env, gc) == 0)
				if (excute_single_command(gc, cmd, &env) == -1)
					return (perror("Excve Error :"), exit(1));
		}
		else
			waitpid(pid, &status, 0);
	}
	dup2(org_stdout, STDOUT_FILENO);
	dup2(org_stdin, STDIN_FILENO);
	close(org_stdin);
	close(org_stdout);
}
