/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:53:37 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/30 09:40:31 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_builtin(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return ("echo");
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return ("cd");
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return ("pwd");
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return ("export");
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return ("unset");
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return ("env");
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return ("exit");
	else
		return (NULL);
}

int	is_builtin_excute(t_gc *gc, t_env **env, t_command *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(*cmd->cmd, "echo", 4) == 0)
		return (my_echo(cmd->cmd), 1);
	else if (ft_strncmp(*cmd->cmd, "cd", 2) == 0)
		return (my_cd(gc, *env, cmd->cmd), 1);
	else if (ft_strncmp(*cmd->cmd, "pwd", 3) == 0)
		return (my_pwd(*env), 1);
	else if (ft_strncmp(*cmd->cmd, "export", 6) == 0)
		return (my_export(gc, env, cmd->cmd), 1);
	else if (ft_strncmp(*cmd->cmd, "unset", 5) == 0)
		return (my_unset(env, cmd->cmd), 1);
	else if (ft_strncmp(*cmd->cmd, "env", 3) == 0)
		return (my_env(*env), 1);
	else if (ft_strncmp(*cmd->cmd, "exit", 4) == 0)
		return (my_exit(cmd->cmd), 1);
	else
		return (0);
}
