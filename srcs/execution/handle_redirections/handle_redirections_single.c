/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_single.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:52:25 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/15 20:58:15 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dup_single(t_command *cmd, int in_file, int out_file)
{
	if (cmd->fd_in != -2 && in_file == -1)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (in_file != -1)
	{
		dup2(in_file, STDIN_FILENO);
		close(in_file);
	}
	if (out_file != -1)
	{
		dup2(out_file, STDOUT_FILENO);
		close(out_file);
	}
}

int	handle_redirections_single(t_command *cmd)
{
	int	out_file;
	int	in_file;
	int	i;

	out_file = -1;
	in_file = -1;
	i = 0;
	while (cmd->inoutfile && cmd->inoutfile[i])
	{
		if (redirection_checker(cmd, &in_file, &out_file, i) == -1)
			return (-1);
		i += 2;
	}
	handle_dup_single(cmd, in_file, out_file);
	return (0);
}
