/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_single.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:52:25 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/14 11:06:08 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int handle_redirections_single (t_command *cmd)
{
	int out_file = -1;
	int in_file = -1;
	int i = 0; 

	while (cmd->inoutfile && cmd->inoutfile[i])
	{
		if (!ft_strcmp(cmd->inoutfile[i], ">>"))
		{
			if (out_file != -1)
				close(out_file);
			out_file = open (cmd->inoutfile[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (out_file == -1)
				return (-1);
		}
		else if (!ft_strcmp(cmd->inoutfile[i], ">"))
		{
			if (out_file != -1)
				close(out_file);
			out_file = open(cmd->inoutfile[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (out_file == -1)
				return (-1);
		}
		else if (!ft_strcmp(cmd->inoutfile[i], "<"))
		{
			printf("am here : <<\n");
			if (out_file != -1)
				close(out_file);
			in_file = open(cmd->inoutfile[i + 1], O_RDONLY);
			if (in_file == -1)
			{
				perror("minishell");
				return (-1);
			}
			dup2(in_file, STDIN_FILENO);
			close(in_file);
		}
		i += 2;
	}
	if (cmd->fd_in != -2 && in_file == -1)
	{
		// printf("my heredoc fd is : %d\n", cmd->fd_in);
		// printf("inoutfile 0 ==> %s\n", cmd->inoutfile[0]);
		// printf("inoutfile 1 ==> %s\n", cmd->inoutfile[1]);
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (out_file != -1)
	{
		dup2(out_file, STDOUT_FILENO);
		close(out_file);
	}
	return 0;
}
