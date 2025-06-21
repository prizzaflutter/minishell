/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_multiple.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:54:25 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/21 10:46:10 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_checker(t_command *cmd, int *out_file, int i)
{
	if (!ft_strcmp(cmd->inoutfile[i], ">>"))
		return (handle_append_redir(cmd, out_file, i));
	else if (!ft_strcmp(cmd->inoutfile[i], ">"))
		return (handle_trunc_redir(cmd, out_file, i));
	else if (!ft_strcmp(cmd->inoutfile[i], "<"))
		return (handle_input_redir(cmd, i));
	else if (!ft_strcmp(cmd->inoutfile[i], "<<"))
		return (handle_herdoc_redir(cmd));
	return (0);
}

int	handle_redirections_multiple(t_command *cmd, int fd_array[])
{
	int	out_file;
	int	i;

	out_file = -1;
	i = 0;
	while (cmd->inoutfile && cmd->inoutfile[i])
	{
		if (redirection_checker(cmd, &out_file, i) == -1)
			return (-1);
		i += 2;
	}
	if (cmd->next && out_file == -1)
	{
		close(fd_array[0]);
		dup2(fd_array[1], STDOUT_FILENO);
		close(fd_array[1]);
	}
	return (1);
}
