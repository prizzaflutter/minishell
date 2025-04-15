#include "minishell.h"

int execute_cmd(t_command *cmd, int *fd_array, t_env *env)
{
	char **cmd_args;
	char *cmd_path;

	close(fd_array[0]);
	dup2(fd_array[1], STDOUT_FILENO);
	close(fd_array[1]);
	cmd_args = cmd->cmd;
	if (!cmd_args)
		return (0);
	cmd_path = configure_path(*cmd->cmd, env);
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
				close(fd_array[1]);
				dup2(fd_array[0], STDIN_FILENO);
				close(fd_array[0]);
			}
			if (cmd->cmd[0] == NULL) 
				return (0);
			if (execute_cmd(current_cmd, fd_array, env) == 0)
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