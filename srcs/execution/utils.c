/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:40:58 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/24 16:25:35 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_of_env(t_env *env)
{
	t_env	*tmp;
	int		size;

	tmp = env;
	size = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	**convert_env_to_array(t_gc *gc, t_env *env)
{
	int		i;
	int		size;
	char	**env_array;
	char	*tmp;

	i = 0;
	env_array = NULL;
	size = size_of_env(env);
	if (!env)
		return (NULL);
	env_array = gc_malloc(gc, sizeof(char *) * (size + 1), 0);
	if (!env_array)
		return (NULL);
	env_array[size] = NULL;
	while (env)
	{
		tmp = gc_strcat(gc, env->key, "=");
		env_array[i] = gc_strcat(gc, tmp, env->value);
		if (!env_array[i])
			return (NULL);
		i++;
		env = env->next;
	}
	return (env_array);
}

void	save_int_out(int *org_int, int *org_out)
{
	*org_int = dup(STDIN_FILENO);
	*org_out = dup(STDOUT_FILENO);
}

void	restore_in_out(int *org_int, int *org_out)
{
	dup2(*org_int, STDIN_FILENO);
	dup2(*org_out, STDOUT_FILENO);
	close(*org_int);
	close(*org_out);
}
