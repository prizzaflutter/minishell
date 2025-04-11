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
			return (ft_printf(2, "Error: Command not found : %s\n", cmd), NULL);
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
	if (!cmd_args)
		return (0);
	cmd_path = configure_path(*cmd->cmd, env);
	if (!cmd_path)
		return (free_args(cmd_args), 0);
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
	if (!cmd_args)
		return (0);
	cmd_path = configure_path(*cmd->cmd, env);
	if (!cmd_path)
		return (free_args(cmd_args), 0);
	if (execve(cmd_path, cmd_args, env) == -1)
	{
		free_args(cmd_args);
		return (printf("Error: EXECVE => (first child)"), 0);
	}
	return (1);
}

// ls -la | cat Makefile

int handle_multiple_command(t_command *cmd, char **env)
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
					ft_printf(2, "error in file descriptor\n");
					return 0;
				}
				dup2(out_file, STDOUT_FILENO);
				close(out_file);
			}
			else if (current_cmd->next)
			{
				close(fd_array[1]);
				dup2(fd_array[0], STDIN_FILENO);
				close(fd_array[0]);
			}
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
	int cmd_size = 0;

	printf("execute_command\n");
	printf("cmd->cmd[0] is : %s\n", cmd->cmd[0]);
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
	{
		perror("Invalid command");
		return;
	}
	cmd_size = ft_cmdsize(cmd);
	if (cmd_size > 1)
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

char *get_line(const char *prompt) {
    char *line = readline(prompt);
    if (line && *line)
        add_history(line);
    return line;
}

char **get_command_args() {
    char **args = malloc(sizeof(char *) * 100);
    int i = 0;
    char *input = get_line("Command (e.g. ls): ");
    args[i++] = input;

    while (1) {
        char prompt[64];
        sprintf(prompt, "Argument #%d (or just ENTER to skip): ", i);
        char *arg = get_line(prompt);
        if (!arg || strlen(arg) == 0) {
            free(arg);
            break;
        }
        args[i++] = arg;
    }
    args[i] = NULL;
    return args;
}

char **get_redirection() {
    char **redir = calloc(3, sizeof(char *));
    redir[0] = get_line("Redirection operator (>, >> or ENTER to skip): ");
    if (redir[0] && strlen(redir[0]) > 0) {
        redir[1] = get_line("Redirection file: ");
    } else {
        free(redir[0]);
        redir[0] = NULL;
    }
    return redir;
}

t_command *create_command() {
    t_command *cmd = calloc(1, sizeof(t_command));
    cmd->cmd = get_command_args();
    cmd->inoutfile = get_redirection();
    return cmd;
}

t_command *build_command_list() {
    t_command *head = NULL;
    t_command *prev = NULL;

    int index = 1;
    while (1) {
        printf("\n--- Command #%d ---\n", index++);
        t_command *cmd = create_command();

        if (!head)
            head = cmd;
        if (prev) {
            prev->next = cmd;
            cmd->prev = prev;
        }
        prev = cmd;

        char *more = get_line("Add a pipe to another command? (y/n): ");
        if (!more || strcmp(more, "y") != 0) {
            free(more);
            break;
        }
        free(more);
    }
    return head;
}

int main(int argc, char *argv[], char **env) {
	(void)argc;
	(void)argv;
    t_command *cmd_list = build_command_list();
	execute_command(cmd_list, env);  // Pass your environment variables here
    return 0;
}
