#include "minishell.h"

int handle_redirections_single (t_command *cmd)
{
	int out_file = -1;
	int i = 0; 
	while (cmd->inoutfile && cmd->inoutfile[i])
	{

		if (!ft_strcmp(cmd->inoutfile[i], ">>"))
		{
			if (out_file == -1)
				close(out_file);
			out_file = open (cmd->inoutfile[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else if (!ft_strcmp(cmd->inoutfile[i], ">"))
		{
			if (out_file == -1)
				close(out_file);
			out_file = open(cmd->inoutfile[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (!ft_strcmp(cmd->inoutfile[i], "<"))
		{
			out_file = open(cmd->inoutfile[1], O_RDONLY);
			if (out_file == -1)
			{
				printf("error in file descriptor single command 2\n");
				return (-1);
			}
			dup2(out_file, STDIN_FILENO);
			close(out_file);
		}
		i += 2;
	}
	if (out_file != -1)
	{
		dup2(out_file, STDOUT_FILENO);
		close(out_file);
	}
	return 0;
}
