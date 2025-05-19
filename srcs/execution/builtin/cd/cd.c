/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:25:43 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/19 13:25:44 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_absolute_path(char *path)
{
	if (!ft_strncmp(path, "/", 1))
		return (1);
	return (0);
}

void	update_pwd(char *path, t_env *env, t_gc *gc)
{
	char	*oldpwd;
	t_env	*curr;

	oldpwd = NULL;
	curr = env;
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

void	append_path_pwd(char *path, t_env *env, t_gc *gc, int flag)
{
	char	*oldpwd;
	t_env	*curr;

	oldpwd = NULL;
	curr = env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, "PWD"))
		{
			oldpwd = curr->value;
			curr->value = normalize_path(curr, gc, path, flag);
			break ;
		}
		curr = curr->next;
	}
	update_oldpwd(gc, env, oldpwd);
}

void	get_home(t_gc *gc, t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, "HOME"))
		{
			my_cd(gc, env, curr->value);
			break ;
		}
		curr = curr->next;
	}
}

int	my_cd(t_gc *gc, t_env *env, char *argv)
{
	char	*cwd;
	t_env	*curr;

	if (!argv)
	{
		curr = env;
		get_home(gc, curr);
		return (0);
	}
	if (chdir(argv) != 0)
		return (perror("cd"), exit_status(1, 1), 0);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror ("cd: error retrieving current directory"),
			ft_printf(2, "getcwd: cannot access parent directories\n"),
			append_path_pwd(argv, env, gc, 0), 0);
	if (is_absolute_path(argv))
		update_pwd(argv, env, gc);
	else
		append_path_pwd(argv, env, gc, 1);
	exit_status(1, 0);
	free(cwd);
	return (0);
}
