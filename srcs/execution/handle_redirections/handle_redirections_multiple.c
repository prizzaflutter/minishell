/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_multiple.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:54:25 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/15 09:42:56 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_checker(t_command *cmd, int *in, int *out, int i)
{
	if (!ft_strcmp(cmd->inoutfile[i], ">>"))
	{
		if (*out != -1)
			close(*out);
		*out = open(cmd->inoutfile[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*out == -1)
			return (-1);
	}
	else if (!ft_strcmp(cmd->inoutfile[i], ">"))
	{
		if (*out != -1)
			close(*out);
		*out = open(cmd->inoutfile[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*out == -1)
			return (-1);
	}
	else if (!ft_strcmp(cmd->inoutfile[i], "<"))
	{
		if (*in != -1)
			close(*in);
		*in = open(cmd->inoutfile[i + 1], O_RDONLY);
		if (*in == -1)
			return (-1);
	}
	return (1);
}

void	handle_dup(t_command *cmd, int in_file, int out_file, int fd_array[])
{
	if (cmd->next && out_file == -1)
	{
		close(fd_array[0]);
		dup2(fd_array[1], STDOUT_FILENO);
		close(fd_array[1]);
	}
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

int	handle_redirections_multiple(t_command *cmd, int fd_array[])
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
	handle_dup(cmd, in_file, out_file, fd_array);
	return (out_file != 1);
}
