/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_single.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:52:25 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/29 15:36:17 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dup_single(t_command *cmd, int in_file, int out_file, int last)
{
	if (cmd->fd_in != -2 && !ft_strcmp(cmd->inoutfile[last], "<<"))
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	else if (in_file != -1 && !ft_strcmp(cmd->inoutfile[last], "<"))
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
	int	last;

	out_file = -1;
	in_file = -1;
	i = 0;
	last = 0;
	while (cmd->inoutfile && cmd->inoutfile[i])
	{
		if (!ft_strcmp(cmd->inoutfile[i], "<<") || !ft_strcmp(cmd->inoutfile[i], "<"))
			last = i;
		if (redirection_checker(cmd, &in_file, &out_file, i) == -1)
			return (perror("minishell"), -1);
		i += 2;
	}
	// printf("the last is : %s\n", cmd->inoutfile[last]);
	// printf("the std in file is : %d\n", in_file);
	// printf("the stdout file is : %d\n", out_file);
	// printf("the fd of heredoc is : %d\n", cmd->fd_in);
	handle_dup_single(cmd, in_file, out_file, last);
	return (0);
}
