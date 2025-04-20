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
	if (is_builtin(*cmd->cmd))
	{
		if (ft_strncmp(*cmd->cmd, "echo", 4) == 0)
			my_echo(cmd_args);
		else if (ft_strncmp(*cmd->cmd, "cd", 2) == 0)
			my_cd(cmd_args);
		else if (ft_strncmp(*cmd->cmd, "pwd", 3) == 0)
			my_pwd();
		else if (ft_strncmp(*cmd->cmd, "export", 6) == 0)
			my_export(gc, env, cmd_args);
		else if (ft_strncmp(*cmd->cmd, "unset", 5) == 0)
			my_unset(env, cmd_args);
		else if (ft_strncmp(*cmd->cmd, "env", 3) == 0)
			my_env(*env);
		// else if (ft_strncmp(*cmd->cmd, "exit", 4) == 0)
		// 	my_exit(cmd_args);
		return (1);
	}

	cmd_path = configure_path(gc, *cmd->cmd, *env);
	printf("the cmd path is %s\n", cmd_path);
	if (!cmd_path)
		return ( 0);
	env_array = convert_env_to_array(gc, *env);
	if (!env_array)
		return ( 0);
	if (execve(cmd_path, cmd_args, env_array) == -1)
	{
		return (printf("Error: EXECVE => (first child)"), 0);
	}
	return (1);
}

int handle_multiple_command(t_gc *gc, t_command *cmd, t_env *env)
{
	int fd_array[2];
	int prev_fd = -1;
	int out_file;
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
			if ((current_cmd->inoutfile && current_cmd->inoutfile[0] && !ft_strncmp(current_cmd->inoutfile[0], ">", 1)) || 
			(current_cmd->inoutfile && current_cmd->inoutfile[0] && !ft_strncmp(current_cmd->inoutfile[0], ">>", 2)))
			{
				ft_printf(2, "the command contains redirection\n");
				if (!ft_strncmp(current_cmd->inoutfile[0], ">>", 2))
					out_file = open(current_cmd->inoutfile[1], O_WRONLY | O_CREAT | O_APPEND , 0642);
				else if(!ft_strncmp(current_cmd->inoutfile[0], ">", 1))
					out_file = open(current_cmd->inoutfile[1], O_WRONLY | O_CREAT | O_TRUNC, 0642);
				if (out_file == -1)
				{
					ft_printf(2, "error in file descriptor 1\n");
					return 0;
				}
				dup2(out_file, STDOUT_FILENO);
				close(out_file);
			}
			// else if (current_cmd->inoutfile && current_cmd->inoutfile[0] && !ft_strncmp(current_cmd->inoutfile[0], "<<", 2))
			// {
			// 	handle_herdoc_infile(current_cmd);
			// }
			else if (current_cmd->inoutfile && current_cmd->inoutfile[0] && !ft_strncmp(current_cmd->inoutfile[0], "<", 1))
			{
				out_file = open(current_cmd->inoutfile[1], O_RDONLY);
				if (out_file == -1)
				{
					ft_printf(2, "error in file descriptor 2\n");
					return 0;
				}
				dup2(out_file, STDIN_FILENO);
				close(out_file);
			}
			else if (current_cmd->next)
			{
				close(fd_array[0]);
				dup2(fd_array[1], STDOUT_FILENO);
				close(fd_array[1]);
			}
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
	while(wait(NULL) > 0);
	return 1;
}