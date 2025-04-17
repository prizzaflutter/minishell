#include "minishell.h"

int excute_single_command(t_command *cmd, t_env **env)
{
	char **cmd_args;
	char *cmd_path;
	char **env_array;

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
	printf("the cmd path is : %s\n", cmd_path);
	if (!cmd_path)
		return (free_args(cmd_args), 0);
	env_array = convert_env_to_array(*env);
	if (!env_array)
	{
		free(cmd_path);
		return (free_args(cmd_args), 0);
	}
	for(int i = 0; env_array[i]; i++)
	{
		printf("env_array[%d]: %s\n", i, env_array[i]);
	}

	if (execve(cmd_path, cmd_args, env_array) == -1)
	{
		free_args(cmd_args);
		return (printf("Error: EXECVE => (first child)"), 0);
	}
	return (1);
}

void handle_single_command(t_command *cmd, t_env *env)
{
	pid_t pid;
	int status;
	int out_file;

	out_file = 0;
	if ((cmd->inoutfile && cmd->inoutfile[0] && !ft_strncmp(cmd->inoutfile[0], ">", 1)) || 
		(cmd->inoutfile && cmd->inoutfile[0] && !ft_strncmp(cmd->inoutfile[0], ">>", 2)))
	{
		printf("the command contains redirection\n");
		if (!ft_strncmp(cmd->inoutfile[0], ">>", 2))
			out_file = open(cmd->inoutfile[1], O_WRONLY | O_CREAT | O_APPEND , 0642);
		else if(!ft_strncmp(cmd->inoutfile[0], ">", 1))
			out_file = open(cmd->inoutfile[1], O_WRONLY | O_CREAT | O_TRUNC, 0642);
		if (out_file == -1)
		{
			printf("error in file descriptor singlle command 1\n");
			return ;
		}
		dup2(out_file, STDOUT_FILENO);
		close(out_file);
	}
	// else if (cmd->inoutfile && cmd->inoutfile[0] && !ft_strncmp(cmd->inoutfile[0], "<<", 2))
	// {
	// 	handle_herdoc_infile(cmd);
	// }
	else if (cmd->inoutfile && cmd->inoutfile[0] && !ft_strncmp(cmd->inoutfile[0], "<", 1))
	{
		out_file = open(cmd->inoutfile[1], O_RDONLY);
		if (out_file == -1)
		{
			printf("error in file descriptor single command 2\n");
			return ;
		}
		dup2(out_file, STDIN_FILENO);
		close(out_file);
	}
	if (cmd->cmd[0] == NULL)
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("Fork error");
		return;
	}
	if (pid == 0)
	{
		if (excute_single_command(cmd, &env) == -1)
		{
			perror("Execve error :");
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}