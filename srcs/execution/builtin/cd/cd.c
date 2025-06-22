/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:25:43 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/21 21:52:04 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(char *path, t_env **env, t_gc *gc)
{
	char	*oldpwd;
	t_env	*curr;

	oldpwd = NULL;
	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, "PWD"))
		{
			oldpwd = curr->value;
			curr->value = gc_strdup(gc, path);
			break ;
		}
		curr = curr->next;
	}
	update_oldpwd(gc, env, oldpwd);
}

void	append_path_pwd(char *path, t_env **env, t_gc *gc)
{
	char	*oldpwd;
	t_env	*curr;

	oldpwd = NULL;
	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, "PWD"))
		{
			if (curr->value)
			{
				oldpwd = curr->value;
				curr->value = normalize_path(curr, gc, path);
			}
			break ;
		}
		curr = curr->next;
	}
	update_oldpwd(gc, env, oldpwd);
}

void	cd_exit(int is_pipe)
{
	if (is_pipe)
		exit(0);
	else
		exit_status(1, 0);
}

int	my_cd(t_gc *gc, t_env **env, char **argv, int is_pipe)
{
	char	*cwd;
	char	content[4096];
	int		len;

	len = get_len(argv);
	if (!to_manay_args(len, is_pipe))
		return (0);
	if (!argv[1])
		return (cd_alone(gc, env, is_pipe), 0);
	if (chdir(argv[1]) != 0)
	{
		if (is_pipe)
			return (perror("minishell: cd"), exit(1), 0);
		else
			return (perror("minishell: cd"), exit_status(1, 1), 0);
	}
	cwd = getcwd(content, sizeof(content));
	if (!cwd)
		return (perror("cd: error retrieving current directory"),
			ft_printf("getcwd: cannot access parent directories\n"),
			append_path_pwd(argv[1], env, gc), 0);
	update_pwd(content, env, gc);
	cd_exit(is_pipe);
	return (0);
}
