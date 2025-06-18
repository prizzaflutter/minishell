/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:25:43 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/17 10:57:04 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_absolute_path(char *path)
{
	if (!ft_strncmp(path, "/", 1))
		return (1);
	return (0);
}

char	*remove_back_slash(t_gc *gc, char *path)
{
	char	**splited_path;
	char	*my_path;

	splited_path = gc_split(gc, path, '/');
	my_path = gc_strjoin(gc, "/", splited_path[0]);
	return my_path;
}
void	update_pwd(char *path, t_env *env, t_gc *gc)
{
	char	*oldpwd;
	t_env	*curr;
	// char 	*my_new_path;

	oldpwd = NULL;
	curr = env;
	while (curr)
	{
		// problem her
		if (!ft_strcmp(curr->key, "PWD"))
		{
			oldpwd = curr->value;
			// my_new_path = remove_back_slash(gc, path);
			// curr->value = gc_strdup(gc, my_new_path);
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

int	get_home(t_gc *gc, t_env *env, int is_pipe)
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
			my_cd(gc, env, args, is_pipe);
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

int	my_cd(t_gc *gc, t_env *env, char **argv, int is_pipe)
{
	char	*cwd;
	t_env	*curr;
	char	content[4096];
	int		len;

	
	len = get_len(argv);
	if (len > 2)
	{
		if (is_pipe)
		{
			ft_printf(2, "minishell: too many argument\n");
			exit(1);
		}
		else
		{
			ft_printf(2, "minishell: too many argument\n");
			exit_status(1, 1, "my cd - 1");
			return(0);
		}
	}
	// if (len > 2)
	// 	return (ft_printf(2, "minishell: too many argument\n"), exit_status(1, 1, "my cd - 1"), 0);
	if (!argv[1])
	{
		curr = env;
		if (get_home(gc, curr, is_pipe) == 0)
		{
			ft_printf(2, "minishell: cd: HOME not set\n");
			if (is_pipe)
			{
				exit(1);
			}
			else 
				exit_status(1, 1, "my cd - 2");
		}
		return (0);
	}
	if (chdir(argv[1]) != 0)
	{
		if (is_pipe)
		{
			perror("minishell: cd");
			exit(1);
		}
		else 
		{
			perror("minishell: cd");
			exit_status(1, 1, "my cd - 3");
			return 0;
		}
	}
	cwd = getcwd(content, sizeof(content));
	if (!cwd)
		return (perror("cd: error retrieving current directory"),
			ft_printf(2, "getcwd: cannot access parent directories\n"),
			append_path_pwd(argv[1], env, gc, 0), 0);
	update_pwd(content, env, gc);
	// if (is_absolute_path(argv[1]))
	// 	update_pwd(content, env, gc);
	// else
	// 	update_pwd(content, env, gc);
	if (is_pipe)
		exit(0);
	else
		exit_status(1, 0, "my cd - 4");
	// free(cwd);
	return (0);
}
