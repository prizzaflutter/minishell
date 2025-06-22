/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utilits.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:46:37 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/22 10:31:00 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_append_redir(t_command *cmd, int *out_file, int i)
{
	*out_file = open(cmd->inoutfile[i + 1], O_WRONLY
			| O_CREAT | O_APPEND, 0644);
	if (*out_file == -1)
		return (ft_printf("Error>>\n"), -1);
	if (dup2(*out_file, STDOUT_FILENO) == -1)
		return (perror("dup2 >>"), -1);
	close(*out_file);
	return (0);
}

int	handle_trunc_redir(t_command *cmd, int *out_file, int i)
{
	*out_file = open(cmd->inoutfile[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*out_file == -1)
		return (ft_printf("Error>\n"), -1);
	if (dup2(*out_file, STDOUT_FILENO) == -1)
		return (perror("dup2 >"), -1);
	close(*out_file);
	return (0);
}

int	handle_input_redir(t_command *cmd, int i)
{
	int	in_file;

	in_file = open(cmd->inoutfile[i + 1], O_RDONLY);
	if (in_file == -1)
		return (ft_printf("Error<\n"), -1);
	if (dup2(in_file, STDIN_FILENO) == -1)
		return (perror("dup2 <"), -1);
	close(in_file);
	return (0);
}

int	handle_herdoc_redir(t_command *cmd)
{
	if (cmd->fd_in != -2)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return (ft_printf("dup2 <<\n"), -1);
		close(cmd->fd_in);
		cmd->fd_in = -2;
	}
	return (0);
}
