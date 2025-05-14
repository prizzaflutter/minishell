/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:28:10 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/13 12:51:43 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_on_parent(char *build_in_f, t_command *cmd, t_env *env, t_gc *gc)
{
	if (!ft_strcmp(build_in_f, "cd") || !ft_strcmp(build_in_f, "unset")
		|| (!ft_strcmp(build_in_f, "export") && cmd->cmd[1] != NULL) || !ft_strcmp(build_in_f, "exit"))
	{
		printf("============ run on parent proccess ==================\n");
		if (!ft_strcmp(build_in_f, "cd"))
			return (my_cd(gc, env, cmd->cmd[1]), 1);
		else if (!ft_strcmp(build_in_f, "unset"))
			return (my_unset(&env, cmd->cmd), 1);
		else if (!ft_strcmp(build_in_f, "export"))
			return (my_export(gc, &env, cmd->cmd), 1);
		else if (!ft_strcmp(build_in_f, "exit"))
			return (my_exit(cmd->cmd), 1);
	}
	return (0);
}

int	is_on_child(char *build_in_f, t_command *cmd, t_env *env, t_gc *gc)
{
	if (!ft_strcmp(build_in_f, "echo"))
		return (my_echo(cmd->cmd), exit_status(1, 0), 1);
	else if (!ft_strcmp(build_in_f, "pwd"))
		return (my_pwd(env), exit_status(1, 0), 1);
	else if (!ft_strcmp(build_in_f, "export") && cmd->cmd[1] == NULL)
		return (my_export(gc, &env, cmd->cmd), 1);
	else if (!ft_strcmp(build_in_f, "env"))
		return (my_env(env), exit_status(1, 0), 1);
	return (0);
}
