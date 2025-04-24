#include "minishell.h"

int handle_redirections_multiple(t_command *current_cmd, int fd_array[])
{
    int out_file;

    out_file = -1;
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
				return (-1);
			}
			dup2(out_file, STDOUT_FILENO);
			close(out_file);
		}
		// else if (current_cmd->inoutfile && current_cmd->inoutfile[0] && !ft_strncmp(current_cmd->inoutfile[0], "<<", 2))
		// {
		// 	handle_herdoc_infile(current_cmd);
		// }ll
		else if (current_cmd->inoutfile && current_cmd->inoutfile[0] && !ft_strncmp(current_cmd->inoutfile[0], "<", 1))
		{
			out_file = open(current_cmd->inoutfile[1], O_RDONLY);
			if (out_file == -1)
			{
				ft_printf(2, "error in file descriptor 2\n");
				return (-1);
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
    return (out_file);
}