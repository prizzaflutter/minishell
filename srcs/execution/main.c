#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void free_command_list(t_command *cmd) {
	while (cmd) {
		t_command *next = cmd->next;

		if (cmd->cmd) {
			for (int i = 0; cmd->cmd[i]; i++)
				free(cmd->cmd[i]);
			free(cmd->cmd);
		}

		if (cmd->inoutfile) {
			for (int i = 0; i < 3 && cmd->inoutfile[i]; i++)
				free(cmd->inoutfile[i]);
			free(cmd->inoutfile);
		}

		free(cmd);
		cmd = next;
	}
}


void execute_command(t_command *cmd, t_env *env)
{
	int cmd_size = 0;

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
	char **redir = calloc(4, sizeof(char *));
	redir[0] = get_line("Redirection (<, >, >>, << or ENTER to skip): ");

	if (redir[0] && strlen(redir[0]) > 0) {
		if (strcmp(redir[0], "<") == 0)
			redir[2] = strdup("in");
		else if (strcmp(redir[0], ">") == 0 || strcmp(redir[0], ">>") == 0)
			redir[2] = strdup("out");
		else if (strcmp(redir[0], "<<") == 0)
			redir[2] = strdup("heredoc");
		else {
			printf("Invalid redirection operator.\n");
			free(redir[0]);
			free(redir);
			return NULL;
		}

		redir[1] = get_line(strcmp(redir[2], "heredoc") == 0 ?
							"Here-document delimiter: " : "Redirection file: ");
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



int env_size (char **env)
{
	int i = 0;
	while(env[i])
		i++;
	return i;
}

void fill_env(t_env *env, char **envp)
{
	int i = 0;
	while(envp[i])
	{
		char *equal_pos = strchr(envp[i], '=');
		if (!equal_pos)
		{
			 i++;
			 continue; 
		}
		size_t key_len = equal_pos - envp[i];
		env[i].key = strndup(envp[i], key_len);
		env[i].value = strdup(equal_pos + 1);
		env[i].next = NULL;
		if (i > 0)
			env[i - 1].next = &env[i];
		i++;
	}
}



int main(int argc, char *argv[], char **env) {
	(void)argc;
	(void)argv;


	int length = env_size(env);
	printf("the length of env is : %d\n", length);
	t_env *env_struct = malloc(sizeof(t_env) * length);
	fill_env(env_struct, env);
	t_env *current = env_struct;
	while(current)
	{
		printf("Key : %s\n", current->key);
		printf("Value : %s\n", current->value);
		current = current->next;
	}
	while (1) {
		t_command *cmd_list = build_command_list();
		if (!cmd_list || !cmd_list->cmd || !cmd_list->cmd[0]) {
			free_command_list(cmd_list);
			continue;
		}
		if (strcmp(cmd_list->cmd[0], "exit") == 0) {
			free_command_list(cmd_list);
			printf("Bye 👋\n");
			break;
		}
		execute_command(cmd_list, env_struct);
		free_command_list(cmd_list); 
	}
	return 0;
}
