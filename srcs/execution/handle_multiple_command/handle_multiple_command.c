
#include "minishell.h"

int	execute_cmd(t_gc *gc, t_command *cmd, t_env **env)
{
	char	**cmd_args;
	char	*cmd_path;
	char	**env_array;

	cmd_args = cmd->cmd;
	if (!cmd_args)
		return (0);
	if (is_builtin_excute(gc, env, cmd))
		exit(0);
	cmd_path = configure_path(gc, *cmd->cmd, *env);
	if (!cmd_path)
		return (0);
	env_array = convert_env_to_array(gc, *env);
	if (!env_array)
		return (0);
	if (execve(cmd_path, cmd_args, env_array) == -1)
	{
		if (errno == EACCES)
			return (ft_printf(2, "minishell: Permission denied\n"), exit(126), 0);
		else if (errno == ENOENT)
			return (ft_printf(2, "minishell: No such file or directory\n"), exit(127), 0);
		else if (errno == EINVAL)
			return (ft_printf(2, "minishell: Invalid executable format\n"), exit(127), 0) ;
	}
	return (1);
}

int	proccess(t_gc *gc, t_env *env, t_command *current_cmd, int *prev_fd, pid_t *last_pid)
{
	pid_t	pid;
	int		fd_array[2];

	if (current_cmd->next && pipe(fd_array) == -1)
		return (perror("Error: pipe issue\n"), 0);
	pid = fork();
	if (pid == -1)
		return (perror("Error: fork issue\n"), 0);
	if (!current_cmd->next)
		*last_pid = pid;
	if (pid == 0)
	{
		child_default_signal();
		if (!child_precess(current_cmd, prev_fd, fd_array))
		{
			ft_printf(2, "exit 1 child process \n");
			exit(1);
		}
		if (!execute_cmd(gc, current_cmd, &env))
		{
			exit(1);
		}
		exit(0);
	}
	else
	{
		parent_process(current_cmd, prev_fd, fd_array);
	}
	return (1);
}

void	waiting(pid_t last_pid, int *flag_squit, int *flag_sint)
{
	int	status;
	pid_t wpid;

	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		perror("signal failed");
	while ((wpid = wait(&status)) > 0)
	{
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT && *flag_squit == 0)
			{
				ft_printf(2, "Quit: 3\n");
				*flag_squit += 1;
			}
			if (WTERMSIG(status) == SIGINT  && *flag_sint == 0)
			{
				ft_printf(2, "\n");
				*flag_sint += 1;
			}
		}
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				exit_status(1, WEXITSTATUS(status), "waiting - 1");
			else if (WIFSIGNALED(status))
				exit_status(1, 128 + WTERMSIG(status), "waiting - 2");
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
	pid_t		last_pid;

	current_cmd = cmd;
	prev_fd = -1; // hada kansavi fih sd in for next command
	save_int_out(&std_int, &std_out);
	while (current_cmd)
	{
		if (proccess(gc, env, current_cmd, &prev_fd, &last_pid) == 0)
			return (0);
		current_cmd = current_cmd->next;
	}
	waiting(last_pid, &flag_sint, &flag_squit);
	restore_in_out(&std_int, &std_out);
	return (1);
}
