/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precess.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:39:37 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/15 11:39:48 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_precess(t_command *current_cmd, int *prev_fd, int *fd_array)
{
	int	out_file;

	if (*prev_fd != -1)
	{
		dup2(*prev_fd, STDIN_FILENO);
		close(*prev_fd);
	}
	out_file = handle_redirections_multiple(current_cmd, fd_array);
	if (out_file == -1)
	{
		printf("the out file == -1\n");
		exit(1);
	}
	if (!out_file && current_cmd->next)
	{
		close(fd_array[0]);
		dup2(fd_array[1], STDOUT_FILENO);
		close(fd_array[1]);
	}
	if (current_cmd->cmd[0] == NULL)
		return (0);
	return (1);
}

void	parent_process(t_command *current_cmd, int *prev_fd, int *fd_array)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current_cmd->next)
	{
		close(fd_array[1]);
		*prev_fd = fd_array[0];
	}
}
