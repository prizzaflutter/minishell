/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:38:01 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/03 17:48:18 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*configure_path(t_gc *gc, char *cmd, t_env *env)
{
	char		*cmd_path;
	struct stat	sb;

	if (!cmd)
		return (NULL);
	cmd_path = get_cmd_path(gc, cmd, env);
	stat(cmd_path, &sb);
	if (!cmd_path)
	{
		if (ft_strchr(cmd, '/')
			&& !access(cmd, F_OK) && !access(cmd, X_OK) && S_ISDIR(sb.st_mode) != 0)
			cmd_path = cmd;
		else
		{
			if (ft_strncmp(cmd, "./", 2))
				return (ft_printf(2, "minishell3: %s: Command not found\n", cmd),
					exit_status(1, 127), exit(127), NULL);
		}
	}
	if (S_ISDIR(sb.st_mode))
		return (printf("minishell:%s : Is a directory\n", cmd_path), exit(126), NULL);
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
	char	*cmd_path;

	if (!cmd || !env)
	{
		printf("the command is : %s\n", cmd);
		return (NULL);
	}
	if (ft_strchr(cmd, '/'))
		return (cmd);
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
			break ;
		env = env->next;
	}
	if (!env || !env->value)
		return (NULL);
	paths = gc_split(gc, env->value, ':');
	if (!paths)
		return (NULL);
	cmd_path = make_path(gc, paths, &cmd);
	return (cmd_path);
}
