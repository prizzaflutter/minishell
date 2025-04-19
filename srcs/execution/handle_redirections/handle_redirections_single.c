#include "minishell.h"

int	handle_redirections_single(t_command *cmd)
{
	int	out_file; 

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
			return (-1);
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
			return (-1);
		}
		dup2(out_file, STDIN_FILENO);
		close(out_file);
	}
	return (out_file);
}
