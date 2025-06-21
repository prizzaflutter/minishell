/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections_single.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:52:25 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/19 11:43:07 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirections_single(t_command *cmd)
{
	int	out_file;
	int	i;

	out_file = -3;
	i = 0;
	while (cmd->inoutfile && cmd->inoutfile[i])
	{
		if (redirection_checker(cmd, &out_file, i) == -1)
			return (perror("minishell5"), -1);
		i += 2;
	}
	return (0);
}
