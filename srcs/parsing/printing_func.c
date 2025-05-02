#include "minishell.h"

void print_list(t_token *tokens)
{
	t_token *current = tokens;

	while (current != NULL)
	{
		printf("Token:\n");
		printf("  -str: %s\n", current->str);
		printf("  -type: %d\n", current->type);
		printf("  -fd_herdoc: %d\n", current->fd_herdoc);
		if (current->type == HEREDOC)
			printf("delimtre = %s\n", current->next->str);
		current = current->next;
	}
}

void print_command_list(t_command *cmds)
{
    t_command *current = cmds;
    int node_index = 0;

    while (current != NULL)
    {
        printf("Node %d:\n", node_index);
        printf("  Commands: ");
        int i = 0;
        while (current->cmd && current->cmd[i])
        {
            printf("[%d] %s ", i, current->cmd[i]);
            i++;
        }
        printf("\n");
        if (current->inoutfile)
        {
            printf("  In/Out files: ");
            i = 0;
            while (current->inoutfile && current->inoutfile[i])
            {
                printf("[%d] %s ", i, current->inoutfile[i]);
                i++;
            }
            printf("\n");
        }
		printf("  fd_in: %d\n", current->fd_in);
        current = current->next;
        node_index++;
    }
}

void read_from_heredoc_fd(int fd)
{
	char buffer[1024];
	ssize_t bytes_read;

	while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		printf("%s", buffer);
	}
	if (bytes_read == -1)
	{
		perror("read");
	}
}

void call_read_from_heredoc_fd(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->fd_herdoc != -2)
		{
			printf("fd_herdoc = %d\n", tokens->fd_herdoc);
			read_from_heredoc_fd(tokens->fd_herdoc);
			printf("*****************************************\n");
		}
		tokens = tokens->next;
	}
}
