#include "minishell.h"

int execute_cmd(t_command *cmd, int *fd_array, t_env **env)
{
	char **cmd_args;
	char *cmd_path;

	close(fd_array[0]);
	dup2(fd_array[1], STDOUT_FILENO);
	close(fd_array[1]);
	cmd_args = cmd->cmd;
	if (!cmd_args)
		return (0);
	if (is_builtin(*cmd->cmd))
	{
		if (ft_strncmp(*cmd->cmd, "echo", 4) == 0)
			my_echo(cmd_args);
		else if (ft_strncmp(*cmd->cmd, "cd", 2) == 0)
			my_cd(cmd_args);
		else if (ft_strncmp(*cmd->cmd, "pwd", 3) == 0)
			my_pwd();
		else if (ft_strncmp(*cmd->cmd, "export", 6) == 0)
			my_export(env, cmd_args);
		else if (ft_strncmp(*cmd->cmd, "unset", 5) == 0)
			my_unset(env, cmd_args);
		else if (ft_strncmp(*cmd->cmd, "env", 3) == 0)
			my_env(*env);
		// else if (ft_strncmp(*cmd->cmd, "exit", 4) == 0)
		// 	my_exit(cmd_args);
		return (1);
	}
	cmd_path = configure_path(*cmd->cmd, *env);
	if (!cmd_path)
		return (free_args(cmd_args), 0);
	if (execve(cmd_path, cmd_args, NULL) == -1)
	{
		free_args(cmd_args);
		return (printf("Error: EXECVE => (first child)"), 0);
	}
	return (1);
}

int handle_multiple_command(t_command *cmd, t_env *env)
{
	int fd_array[2];
	int prev_fd = -1;
	int out_file = 0;
	pid_t pid;
	t_command *current_cmd = cmd;

	while(current_cmd)
	{
		if (current_cmd->next)
		{
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
			out_file = handle_redirections_multiple(current_cmd, fd_array);
			if(out_file == -1 && current_cmd->next)
			{
				close(fd_array[1]);
				dup2(fd_array[0], STDIN_FILENO);
				close(fd_array[0]);
			}
			if (cmd->cmd[0] == NULL) 
				return (0);
			if (execute_cmd(current_cmd, fd_array, &env) == 0)
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
	while(wait(NULL) > 0);
	return 1;
}