
#include "minishell.h"

int	excute_single_command(t_gc *gc, t_command *cmd, t_env **env)
{
	char	**cmd_args;
	char	*cmd_path;
	char	**env_array;

	cmd_args = cmd->cmd;
	cmd_path = configure_path(gc, *cmd->cmd, *env);
	env_array = convert_env_to_array(gc, *env);
	if (execve(cmd_path, cmd_args, env_array) == -1)
	{
		if (errno == EACCES)
			return (printf("minishell: Permission denied\n"), exit_status(1, 126), exit(126), 0);
		else if (errno == ENOENT)
			return (printf("minishell: No such file or directory\n"), exit_status(1, 127), exit(127), 0);
		else if (errno == EINVAL)
			return (printf("minishell: Invalid executable format\n"), exit_status(1, 127), exit(127), 0) ;
		else if (errno == ENOEXEC) 
			return (exit_status(1, 0), exit(0), 0);
	}
	return (1);
}

void	handle_redirection_and_execute(char *build_in_f,
	t_gc *gc, t_command *cmd, t_env *env)
{
	int		out_file;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		child_default_signal();
		out_file = handle_redirections_single(cmd);
		if (out_file == -1)
			exit(1);
		if (is_on_child(build_in_f, cmd, env, gc) == 0)
			excute_single_command(gc, cmd, &env);
		exit(0);
	}
	else
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR)
			perror("signal failed");
		waitpid(pid, &status, 0);
		call_main_signals();
		if (WIFEXITED(status))
			exit_status(1, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			exit_status(1, 128 + WTERMSIG(status));
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			printf("Quit: 3\n");
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			printf("\n");
	}
}

void	handle_single_command(t_gc *gc, t_command *cmd, t_env **env)
{
	char	*build_in_f;
	int		org_stdin ;
	int		org_stdout;

	save_int_out(&org_stdin, &org_stdout);
	if ((cmd->cmd[0] == NULL && cmd->inoutfile[0] == NULL))
		{
			printf("am over her\n");
			return ;
		}
	build_in_f = is_builtin(*cmd->cmd);
	if (is_on_parent(build_in_f, cmd, env, gc) == 0)
		handle_redirection_and_execute(build_in_f, gc, cmd, *env);
	restore_in_out(&org_stdin, &org_stdout);
}
