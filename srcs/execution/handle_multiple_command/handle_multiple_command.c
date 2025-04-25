#include "minishell.h"

int execute_cmd(t_gc *gc,t_command *cmd, int *fd_array, t_env **env)
{
	char **cmd_args;
	char *cmd_path;
	char **env_array;

	close(fd_array[0]);
	dup2(fd_array[1], STDOUT_FILENO);
	close(fd_array[1]);
	cmd_args = cmd->cmd;
	if (!cmd_args)
		return (0);
	if (is_builtin_excute(gc, env, cmd) == 1)
		return (1);
	cmd_path = configure_path(gc, *cmd->cmd, *env);
	if (!cmd_path)
		return ( 0);
	env_array = convert_env_to_array(gc, *env);
	if (!env_array)
		return (0);
	if (execve(cmd_path, cmd_args, env_array) == -1)
		return (printf("Error: EXECVE => (first child)"), exit_status(1, 127), 1);
	return (1);
}

int handle_multiple_command(t_gc *gc, t_command *cmd, t_env *env)
{
	int fd_array[2];
	int prev_fd = -1;
	int out_file;
	int status;
	pid_t pid;
	t_command *current_cmd = cmd;

	while(current_cmd)
	{
		if (current_cmd->next)
		{
			printf("pipe over here\n");
			if (pipe(fd_array) == -1)
			{
				printf("Error: pipe issue\n");
				return 0;
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return 0;
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			out_file = handle_redirections_single(cmd);
			if (out_file == -1)
				exit(1);
			if (cmd->cmd[0] == NULL) 
				return (0);
			if (execute_cmd(gc, current_cmd, fd_array, &env) == 0)
			{
				close(fd_array[1]);
				close(fd_array[0]);
				exit(1);
			}
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (current_cmd->next)
			{
				close(fd_array[1]);
				prev_fd = fd_array[0];
			}
		}
		current_cmd = current_cmd->next;
	}
	while(wait(&status) > 0)
	{
		if (WIFEXITED(status))
			exit_status(1, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			exit_status(1, 128 + WTERMSIG(status));
	}
	return 1;
}