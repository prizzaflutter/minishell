/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 06:42:12 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/24 13:11:34 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *configure_path(t_gc *gc, char *cmd, t_env *env)
{
	char *cmd_path;

	cmd_path = get_cmd_path(gc, cmd, env);
	if (!cmd_path)
	{
		if ((!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1))
			&& !access(cmd, F_OK) && !access(cmd, X_OK))
			cmd_path = cmd;
		else
			return (ft_printf(2, "Error: Command not found : %s\n", cmd), exit_status(1, 127), NULL);
	}
	return (cmd_path);
}

char	*make_path(t_gc *gc, char **paths, char **tmp)
{
	char	*tmp_path;
	char	*cmd_path;
	int		i;

	tmp_path = NULL;
	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		tmp_path = gc_strjoin(gc, paths[i], "/");
		cmd_path = gc_strjoin(gc, tmp_path, tmp[0]);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_gc *gc, char *cmd, t_env *env)
{
	char	**paths;
	char	**tmp;
	char	*cmd_path;

	if (!cmd || !env)
		return (NULL);
	while(env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
			break;
		env = env->next;
	}
	if (!env || !env->value)
		return (NULL);
	paths = gc_split(gc, env->value, ':');
	tmp = gc_split(gc, cmd, ' ');
	if (!paths || !tmp)
		return (NULL);
	cmd_path = make_path(gc, paths, tmp);
	return (cmd_path);
}
