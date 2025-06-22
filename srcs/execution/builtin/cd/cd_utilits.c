/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utilits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:00:29 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/21 21:51:54 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_home(t_gc *gc, t_env **env, int is_pipe)
{
	t_env	*curr;
	int		result;
	char	**args;

	curr = *env;
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
	while (argv[size] != NULL)
		size++;
	return (size);
}

int	is_absolute_path(char *path)
{
	if (!ft_strncmp(path, "/", 1))
		return (1);
	return (0);
}

int	to_manay_args(int len, int is_pipe)
{
	if (len > 2)
	{
		if (is_pipe)
			return (ft_printf("minishell: too many argument\n"),
				exit(1), 0);
		else
			return (ft_printf("minishell: too many argument\n"),
				exit_status(1, 1), 0);
	}
	return (1);
}

void	cd_alone(t_gc *gc, t_env **env, int is_pipe)
{
	if (get_home(gc, env, is_pipe) == 0)
	{
		ft_printf("minishell: cd: HOME not set\n");
		if (is_pipe)
			exit(1);
		else
			exit_status(1, 1);
	}
}
