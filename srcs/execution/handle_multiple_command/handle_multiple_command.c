
#include "minishell.h"

int	execute_cmd(t_gc *gc, t_command *cmd, t_env **env)
{
	char	**cmd_args;
	char	*cmd_path;
	char	**env_array;

	cmd_args = cmd->cmd;
	if (!cmd_args)
		return (0);
	if (is_builtin_excute(gc, env, cmd) == 1)
		return (1);
	cmd_path = configure_path(gc, *cmd->cmd, *env);
	if (!cmd_path)
		return (0);
	env_array = convert_env_to_array(gc, *env);
	if (!env_array)
		return (0);
	if (execve(cmd_path, cmd_args, env_array) == -1)
		return (exit_status(1, 127), 1);
	return (1);
}

int	proccess(t_gc *gc, t_env *env, t_command *current_cmd, int *prev_fd)
{
	pid_t	pid;
	int		fd_array[2];

	if (current_cmd->next && pipe(fd_array) == -1)
		return (perror("Error: pipe issue\n"), 0);
	pid = fork();
	if (pid == -1)
		return (perror("Error: fork issue\n"), 0);
	if (pid == 0)
	{
		child_default_signal();
		if (!child_precess(current_cmd, prev_fd, fd_array))
			exit(1);
		if (!execute_cmd(gc, current_cmd, &env))
			exit(1);
		exit(0);
	}
	else
		parent_process(current_cmd, prev_fd, fd_array);
	return (1);
}

void	waiting(int *flag_squit, int *flag_sint)
{
	int	status;

	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		perror("signal failed");
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			exit_status(1, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			exit_status(1, 128 + WTERMSIG(status));
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT && *flag_squit == 0)
		{
			printf("Quit: 3\n");
			*flag_squit += 1;
		}
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT  && *flag_sint == 0)
		{
			printf("\n");
			*flag_sint += 1;
		}
	}
}

int	handle_multiple_command(t_gc *gc, t_command *cmd, t_env *env)
{
	t_command	*current_cmd;
	int			prev_fd;
	int			std_int;
	int			std_out;
	int			flag_sint = 0;
	int			flag_squit = 0;

	current_cmd = cmd;
	prev_fd = -1; // hada kansavi fih sd in for next command
	save_int_out(&std_int, &std_out);
	while (current_cmd)
	{
		if (proccess(gc, env, current_cmd, &prev_fd) == 0)
			return (0);
		current_cmd = current_cmd->next;
	}
	waiting(&flag_sint, &flag_squit);
	restore_in_out(&std_int, &std_out);
	return (1);
}
