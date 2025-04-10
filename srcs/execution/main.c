#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *configure_path(char *cmd, char **env)
{
    char *cmd_path;

    cmd_path = get_cmd_path(cmd, env);  // Assuming this is defined elsewhere
    if (!cmd_path)
    {
        if ((!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1))
            && !access(cmd, F_OK) && !access(cmd, X_OK))
            cmd_path = cmd;
        else
            return (printf("Error: Command not found : %s\n", cmd), NULL);
    }
    return (cmd_path);
}

int execute_cmd(t_command *cmd, int *fd_array, char **env)
{
    char **cmd_args;
    char *cmd_path;

    close(fd_array[0]);
    dup2(fd_array[1], STDOUT_FILENO);
    close(fd_array[1]);
    cmd_args = cmd->cmd;
	printf("the cmd is : %s\n", cmd_args[0]);
    if (!cmd_args)
        return (0);
    cmd_path = configure_path(*cmd->cmd, env);
    if (!cmd_path)
        return (free_args(cmd_args), 0);
	printf("the command is : %s\n", cmd_path);
    if (execve(cmd_path, cmd_args, env) == -1)
    {
        free_args(cmd_args);
        return (printf("Error: EXECVE => (first child)"), 0);
    }
    return (1);
}

int excute_single_command(t_command *cmd, char **env)
{
    char **cmd_args;
    char *cmd_path;

    cmd_args = cmd->cmd;
	printf("the cmd is : %s\n", cmd_args[0]);
    if (!cmd_args)
        return (0);
    cmd_path = configure_path(*cmd->cmd, env);
    if (!cmd_path)
        return (free_args(cmd_args), 0);
	printf("the command is : %s\n", cmd_path);
    if (execve(cmd_path, cmd_args, env) == -1)
    {
        free_args(cmd_args);
        return (printf("Error: EXECVE => (first child)"), 0);
    }
    return (1);
}

int handle_multiple_command(t_command *cmd, char **env)
{
    int fd_array[2];
    pid_t pid;

    if (pipe(fd_array) == -1)
    {
        printf("Error: pipe issue\n");
        return 0;
    }
    pid = fork();
    if (pid == -1)
    {
        printf("Error : fork issue\n");
        return 0;
    }
    if (pid == 0)
    {
		printf("execute command over here \n");
        if (execute_cmd(cmd, fd_array, env) == 0)
        {
            close(fd_array[1]);
            close(fd_array[0]);
            exit(1);
        }
    }
    else
    {
        close(fd_array[1]);
        dup2(fd_array[0], STDIN_FILENO);
        close(fd_array[0]);
        return 1;
    }
    return 1;
}

void handle_single_command(t_command *cmd, char **env)
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
			printf("error in file descriptor\n");
			return ;
		}
		dup2(out_file, STDOUT_FILENO);
		close(out_file);
	}
    pid = fork();
    if (pid == -1)
    {
        perror("Fork error");
        return;
    }
    if (pid == 0)
    {
		printf("the cmd is : %s\n", cmd->cmd[0]);
        if (excute_single_command(cmd, env) == -1)
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

void execute_command(t_command *cmd, char **env)
{
    if (!cmd || !cmd->cmd || !cmd->cmd[0])
    {
        perror("Invalid command");
        return;
    }
    if (cmd->next && ft_strncmp(cmd->next, "|", 1) == 0)
    {
		printf("handle multiple command\n");
        handle_multiple_command(cmd, env);
    }
    else
    {
		printf("hanldle single command\n");
        handle_single_command(cmd, env);
    }
}

// command : cat Makefile | grep ^NAME >output.txt

int main(int argc, char *argv[], char **env)
{
    (void)argc;
    (void)argv;

    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
    {
        perror("malloc failed");
        return 1;
    }

    cmd->cmd = malloc(sizeof(char *) * 3);  // Allocate memory for cmd array
    if (!cmd->cmd)
    {
        perror("malloc failed");
        return 1;
    }
    cmd->cmd[0] = strdup("ls");
	// cmd->cmd[1] = strdup("-la");
    cmd->cmd[2] = NULL;
    
    cmd->inoutfile = malloc(sizeof(char *) * 1);  // Allocate memory for inoutfile
    cmd->inoutfile[0] = ">";
	cmd->inoutfile[1] = "output.text";
    cmd->next = NULL;
    cmd->prev = NULL;

    // t_command *cmd2 = malloc(sizeof(t_command));
    // if (!cmd2)
    // {
    //     perror("malloc failed");
    //     return 1;
    // }

    // cmd2->cmd = malloc(sizeof(char *) * 3);
    // if (!cmd2->cmd)
    // {
    //     perror("malloc failed");
    //     return 1;
    // }
    // cmd2->cmd[0] = strdup("grep");
    // cmd2->cmd[1] = strdup("NAME");
    // cmd2->cmd[2] = NULL;

    // cmd2->inoutfile = malloc(sizeof(char *) * 2);
    // cmd2->inoutfile[0] = strdup(">output.txt");
    // cmd2->inoutfile[1] = NULL;

    // cmd2->next = NULL;
    // cmd2->prev = strdup("|");

    execute_command(cmd, env);
    return 0;
}
