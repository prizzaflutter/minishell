#include "minishell.h"

int excute_single_command(t_command *cmd, t_env **env)
{
	char **cmd_args;
	char *cmd_path;
	char **env_array;

	cmd_args = cmd->cmd;
	if (!cmd_args)
		return (0);
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

	
	if (cmd->cmd[0] == NULL)
		return ;
	if (is_builtin(*cmd->cmd))
	{
		printf("the build in function run on the parent proccess\n");
		if (ft_strncmp(*cmd->cmd, "echo", 4) == 0)
			my_echo(cmd->cmd);
		else if (ft_strncmp(*cmd->cmd, "cd", 2) == 0)
			my_cd(cmd->cmd);
		else if (ft_strncmp(*cmd->cmd, "pwd", 3) == 0)
			my_pwd();
		else if (ft_strncmp(*cmd->cmd, "export", 6) == 0)
			my_export(&env, cmd->cmd);
		else if (ft_strncmp(*cmd->cmd, "unset", 5) == 0)
			my_unset(&env, cmd->cmd);
		else if (ft_strncmp(*cmd->cmd, "env", 3) == 0)
			my_env(env);
		// else if (ft_strncmp(*cmd->cmd, "exit", 4) == 0)
		// 	my_exit(cmd_args);
		return ;
	}
	else 
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Fork error");
			return;
		}
		if (pid == 0)
		{
			out_file = handle_redirections_single(cmd);
				if (out_file == -1)
					exit(1);
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
	
}