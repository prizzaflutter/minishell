/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:39:46 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/20 12:41:15 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_key_value(t_gc *gc, char *str)
{
	char	**result;
	char	*equal_pos;

	equal_pos = ft_strchr(str, '=');
	result = gc_malloc(gc, sizeof(char *) * 3);
	if (!result)
		return NULL;
	if (!equal_pos)
	{
		result[0] = gc_strdup(gc, str);
		result[1] = NULL;
	}
	else
	{
		result[0] = gc_strndup(gc, str, equal_pos - str);
		result[1] = gc_strdup(gc, equal_pos + 1);
	}
	
	result[2] = NULL;
	return result;
}

int is_valid_identifier(const char *str)
{
	if (!str || !*str)
		return 0;
	if (!ft_isalpha(*str) && *str != '_')
		return 0;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return 0;
		str++;
	}
	return 1;
}

void	no_args(t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (current->value)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("declare -x %s\n", current->key);
		current = current->next;
	}
}

void	add_new_env(char *key, char *value, t_gc *gc, t_env **env)
{
	t_env *new_env;

	new_env = gc_malloc(gc, sizeof(t_env));
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
		t_env *last = *env;
		while (last->next)
			last = last->next;
		last->next = new_env;
	}
}

void update_value(char *key, char *value, t_env **env, t_gc *gc)
{
	t_env	*current;
	t_env	*found;
	
	current = *env;
	found = NULL;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			found = current;
			break;
		}
		current = current->next;
	}
	if (found)
	{
		if (value)
			found->value = gc_strdup(gc, value);
	}
	else
		add_new_env(key, value, gc, env);
}
