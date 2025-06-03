/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:25:43 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/30 11:45:56 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_absolute_path(char *path)
{
	if (!ft_strncmp(path, "/", 1))
		return (1);
	return (0);
}

char 	*remove_back_slash(t_gc *gc, char *path)
{
	char **splited_path;
	char	*my_path;

	splited_path = gc_split(gc, path, '/');
	my_path = gc_strjoin(gc, "/", splited_path[0]);
	printf("my path is : %s\n", my_path);
	return my_path;
}
void	update_pwd(char *path, t_env *env, t_gc *gc)
{
	char	*oldpwd;
	t_env	*curr;
	char 	*my_new_path;

	oldpwd = NULL;
	curr = env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, "PWD"))
		{
			oldpwd = curr->value;
			my_new_path = remove_back_slash(gc, path);
			curr->value = gc_strdup(gc, my_new_path);;
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
			if (curr->value)
			{
				oldpwd = curr->value;
				curr->value = normalize_path(curr, gc, path, flag);
			}
			break ;
		}
		curr = curr->next;
	}
	update_oldpwd(gc, env, oldpwd);
}

int	get_home(t_gc *gc, t_env *env)
{
	t_env	*curr;
	int		result;
	char	**args;

	curr = env;
	result = 0;
	while (curr)
	{
		if (!ft_strcmp(curr->key, "HOME"))
		{
			args = gc_malloc(gc, sizeof(char *) * 3, 0);
			args[0] = gc_strdup(gc, "cd");
			args[1] = gc_strdup(gc, curr->value);
			args[2] = NULL;
			my_cd(gc, env, args);
			result = 1;
			break ;
		}
		curr = curr->next;
	}
	return (result);
}

int	get_len(char **argv)
{
	int	size;

	size = 0;
	if (!argv || !argv[0])
		return (size);
	while(argv[size] != NULL)
		size++;
	return (size);
}

int	my_cd(t_gc *gc, t_env *env, char **argv)
{
	char	*cwd;
	t_env	*curr;
	int		len;


	len = get_len(argv);
	if (len > 2)
		return (printf("minishell: too many argument\n"), exit_status(1, 1), 0);
	if (!argv[1])
	{
		curr = env;
		if (get_home(gc, curr) == 0)
		{
			printf("minishell: cd: HOME not set\n");
			exit_status(1, 1);
		}
		return (0);
	}
	if (chdir(argv[1]) != 0)
		return (perror("minishell: cd"), exit_status(1, 1), 0);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror ("cd: error retrieving current directory"),
			ft_printf(2, "getcwd: cannot access parent directories\n"),
			append_path_pwd(argv[1], env, gc, 0), 0);
	if (is_absolute_path(argv[1]))
		update_pwd(argv[1], env, gc);
	else
		append_path_pwd(argv[1], env, gc, 1);
	exit_status(1, 0);
	free(cwd);
	return (0);
}
