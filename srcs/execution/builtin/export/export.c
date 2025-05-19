/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:04:38 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/19 13:16:03 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_env(char *key, char *value, t_gc *gc, t_env **env)
{
	t_env	*new_env;
	t_env	*last;

	new_env = gc_malloc(gc, sizeof(t_env), 0);
	if (!new_env)
		return ;
	new_env->key = key;
	if (value)
		new_env->value = gc_strdup(gc, value);
	else
		new_env->value = NULL;
	new_env->next = NULL;
	if (!*env)
		*env = new_env;
	else
	{
		last = *env;
		while (last->next)
			last = last->next;
		last->next = new_env;
	}
}

void	update_value(char **key_value,
	t_env **env, t_gc *gc, int is_append)
{
	t_env	*current;
	t_env	*found;

	current = *env;
	found = NULL;
	while (current)
	{
		if (strcmp(current->key, key_value[0]) == 0)
		{
			found = current;
			break ;
		}
		current = current->next;
	}
	if (found)
	{
		if (key_value[1] && is_append)
			found->value = gc_strjoin_1(gc, found->value, key_value[1]);
		else if (key_value[1])
			found->value = gc_strdup(gc, key_value[1]);
	}
	else
		add_new_env(key_value[0], key_value[1], gc, env);
}

int	checker(char *key, char *value)
{
	if (!is_valid_identifier(key))
	{
		if (value)
			printf("export: `%s%s`: not a valid identifier\n", key, value);
		else
			printf("export: `%s`: not a valid identifier\n", key);
		exit_status(1, 1);
		return (0);
	}
	else
	{
		exit_status(1, 0);
		return (1);
	}
}

void	fill_key_value(t_gc *gc, t_env **env, char *arg)
{
	char	*key;
	char	*value;
	char	**key_value;
	int		is_append;

	key_value = split_key_value(gc, arg, &is_append);
	if (key_value)
	{
		key = key_value[0];
		value = key_value[1];
	}
	else
	{
		key = gc_strdup(gc, arg);
		value = NULL;
	}
	if (!checker(key, value))
		return ;
	if (!key_value)
	{
		key_value[0] = key;
		key_value[1] = value;
	}
	update_value(key_value, env, gc, is_append);
}

void	my_export(t_gc *gc, t_env **env, char **cmd_args)
{
	int	i;

	i = 1;
	if (!cmd_args[1])
	{
		if (!*env)
			return ;
		return (no_args(*env, gc));
	}
	while (cmd_args[i])
	{
		fill_key_value(gc, env, cmd_args[i]);
		i++;
	}
}
