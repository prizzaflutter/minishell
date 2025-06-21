/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:38:28 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/21 09:50:50 by iaskour          ###   ########.fr       */
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
		return (0);
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
