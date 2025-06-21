/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:58:50 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/21 10:06:08 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_gc *gc, t_command *cmd, t_env **env)
{
	int					cmd_size;
	int					flag_sint;
	int					flag_squit;
	t_process_context	*ctx;

	flag_sint = 0;
	flag_squit = 0;
	cmd_size = ft_cmdsize(cmd);
	ctx = NULL;
	if (cmd_size > 1)
	{
		ctx = gc_malloc(gc, sizeof(t_process_context), 0);
		ctx->gc = gc;
		ctx->env = env;
		ctx->flag_sint = &flag_sint;
		ctx->flag_squit = &flag_squit;
		handle_multiple_command(ctx, cmd);
	}
	else
		handle_single_command(gc, cmd, env);
}
