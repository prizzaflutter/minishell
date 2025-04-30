/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:58:50 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/30 14:59:03 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_gc *gc, t_command *cmd, t_env *env)
{
	int	cmd_size;

	cmd_size = ft_cmdsize(cmd);
	if (cmd_size > 1)
		handle_multiple_command(gc, cmd, env);
	else
		handle_single_command(gc, cmd, env);
}
