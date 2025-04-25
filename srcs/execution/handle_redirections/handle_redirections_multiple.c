/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_multiple.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:54:25 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/25 10:59:06 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo "hello world" >> aa.txt >> bb.txt >>  cc.txt | echo "world hello" >> 1.txt >> 2.txt >> 3.txt

int handle_redirections_multiple(t_command *cmd, int fd_array[])
{
    int out_file;
	int	in_file;
	int	i;
	(void)fd_array;

    out_file = -1;
	i = 0;
	while (cmd->inoutfile && cmd->inoutfile[i])
	{
		if (!ft_strcmp(cmd->inoutfile[i], ">>"))
		{
			if (out_file != -1)
				close(out_file);
			out_file = open (cmd->inoutfile[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if ( out_file == -1)
				return (-1);
		}
		else if (!ft_strcmp(cmd->inoutfile[i], ">"))
		{
			if (out_file != -1)
				close(out_file);
			out_file = open(cmd->inoutfile[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(out_file)
				return (-1);
		}
		else if (!ft_strcmp(cmd->inoutfile[i], "<"))
		{
			in_file = open(cmd->inoutfile[i + 1], O_RDONLY);
			if (in_file == -1)
			{
				printf("error in file descriptor single command 2\n");
				return (-1);
			}
			dup2(in_file, STDIN_FILENO);
			close(in_file);
		}
		i += 2;
	}
	if (cmd->next && out_file == -1)
	{
		close(fd_array[0]);
		dup2(fd_array[1], STDOUT_FILENO);
		close(fd_array[1]);
	}
	if (out_file != -1)
	{
		dup2(out_file, STDOUT_FILENO);
		close(out_file);
	}
    return (out_file != 1);
}