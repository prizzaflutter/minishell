/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 06:42:12 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/15 11:38:27 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *configure_path(char *cmd, t_env *env)
{
	char *cmd_path;

	cmd_path = get_cmd_path(cmd, env);  // Assuming this is defined elsewhere
	if (!cmd_path)
	{
		if ((!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1))
			&& !access(cmd, F_OK) && !access(cmd, X_OK))
			cmd_path = cmd;
		else
			return (ft_printf(2, "Error: Command not found over here= : %s\n", cmd), NULL);
	}
	return (cmd_path);
}

char	*make_path(char **paths, char **tmp)
{
	char	*tmp_path;
	char	*cmd_path;
	int		i;

	tmp_path = NULL;
	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp_path, tmp[0]);
		free(tmp_path);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_env *env)
{
	int		i;
	char	**paths;
	char	**tmp;
	char	*cmd_path;

	if (!cmd || !env)
		return (NULL);
	i = 0;
	while(env[i].key)
	{
		if (ft_strncmp(env[i].key, "PATH", 4) == 0)
			break;
		i++;
	}
	printf("the env in i is : %s\n", env[i].key);
	if (!env[i].key)
		return (NULL);
	paths = ft_split(env[i].value, ':');
	tmp = ft_split(cmd, ' ');
	if (!paths || !tmp)
		return (free(paths), free(tmp), NULL);
	cmd_path = make_path(paths, tmp);
	free(paths);
	free(tmp);
	return (cmd_path);
}
