/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 06:42:12 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/10 11:53:57 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_cmd_path(char *cmd, char**env)
{
	int		i;
	char	**paths;
	char	**tmp;
	char	*cmd_path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	tmp = ft_split(cmd, ' ');
	if (!paths || !tmp)
		return (free(paths), free(tmp), NULL);
	cmd_path = make_path(paths, tmp);
	free(paths);
	free(tmp);
	return (cmd_path);
}
