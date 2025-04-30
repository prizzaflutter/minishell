/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:28:10 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/30 16:11:05 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_on_parent(char *build_in_f, t_command *cmd, t_env *env, t_gc *gc)
{
	if (!ft_strcmp(build_in_f, "cd") || !ft_strcmp(build_in_f, "unset")
		|| (!ft_strcmp(build_in_f, "export") && cmd->cmd[1] != NULL))
	{
		printf("============ run on parent proccess ==================\n");
		if (!ft_strcmp(build_in_f, "cd"))
			return (my_cd(cmd->cmd), exit_status(1, 0), 1);
		else if (!ft_strcmp(build_in_f, "unset"))
			return (my_unset(&env, cmd->cmd), exit_status(1, 0), 1);
		else if (!ft_strcmp(build_in_f, "export"))
			return (my_export(gc, &env, cmd->cmd), exit_status(1, 0), 1);
		// else if (ft_strcmp(build_in_f, "exit"))
		// 	my_exit(cmd->cmd);
	}
	return (0);
}

int	is_on_child(char *build_in_f, t_command *cmd, t_env *env, t_gc *gc)
{
	if (!ft_strcmp(build_in_f, "echo"))
		return (my_echo(cmd->cmd), exit_status(1, 0), 1);
	else if (!ft_strcmp(build_in_f, "pwd"))
		return (my_pwd(), exit_status(1, 0), 1);
	else if (!ft_strcmp(build_in_f, "export") && cmd->cmd[1] == NULL)
		return (my_export(gc, &env, cmd->cmd), exit_status(1, 0), 1);
	else if (!ft_strcmp(build_in_f, "env"))
		return (my_env(env), exit_status(1, 0), 1);
	return (0);
}
