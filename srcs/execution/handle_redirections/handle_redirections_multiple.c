/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_multiple.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:54:25 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/18 15:37:17 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	redirection_checker(t_command *cmd, int *in, int *out, int i)
// {
// 	if (!ft_strcmp(cmd->inoutfile[i], ">>"))
// 	{
// 		if (*out != -1)
// 			close(*out);
// 		*out = open(cmd->inoutfile[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (*out == -1)
// 			return (-1);
// 	}
// 	else if (!ft_strcmp(cmd->inoutfile[i], ">"))
// 	{
// 		if (*out != -1)
// 			close(*out);
// 		*out = open(cmd->inoutfile[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (*out == -1)
// 			return (-1);
// 	}
// 	else if (!ft_strcmp(cmd->inoutfile[i], "<"))
// 	{
// 		if (*in != -1)
// 			close(*in);
// 		*in = open(cmd->inoutfile[i + 1], O_RDONLY);
// 		if (*in == -1)
// 			return (-1);
// 	}
// 	return (1);
// }

int	redirection_checker(t_command *cmd, int *out_file, int i)
{
	int	fd;

	if (!ft_strcmp(cmd->inoutfile[i], ">>"))
	{
		*out_file = open(cmd->inoutfile[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*out_file == -1)
			return (-1);
		if (dup2(*out_file, STDOUT_FILENO) == -1)
			return (perror("dup2 >>"), -1);
		close(*out_file);
	}
	else if (!ft_strcmp(cmd->inoutfile[i], ">"))
	{
		*out_file = open(cmd->inoutfile[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*out_file == -1)
			return ( -1);
		if (dup2(*out_file, STDOUT_FILENO) == -1)
			return (perror("dup2 >"), -1);
		close(*out_file);
	}
	else if (!ft_strcmp(cmd->inoutfile[i], "<"))
	{
		fd = open(cmd->inoutfile[i + 1], O_RDONLY);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("dup2 <"), -1);
		close(fd);
	}
	else if (!ft_strcmp(cmd->inoutfile[i], "<<"))
	{
		if (cmd->fd_in != -2)
		{
			if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
				return (perror("dup2 <<"), -1);
			close(cmd->fd_in);
		}
	}
	return (*out_file);
}



int	handle_redirections_multiple(t_command *cmd, int fd_array[])
{
	int	out_file;
	// int	in_file;
	(void)fd_array;
	int	i;
	// int last;

	out_file = -1;
	// in_file = -1;
	i = 0;
	// last = 0;
	while (cmd->inoutfile && cmd->inoutfile[i])
	{
		// if (!ft_strcmp(cmd->inoutfile[i], "<<") || !ft_strcmp(cmd->inoutfile[i], "<"))
		// 	last = i;
		if (redirection_checker(cmd, &out_file, i) == -1)
			return (perror("minishell6"), -1);
		i += 2;
	}
	if (cmd->next && out_file == -1)
	{
		close(fd_array[0]);
		dup2(fd_array[1], STDOUT_FILENO);
		close(fd_array[1]);
	}
	
	// handle_dup(cmd, in_file, out_file, fd_array, last);
	// return (out_file != -1);
	return (1);
}
