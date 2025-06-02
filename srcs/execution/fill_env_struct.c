/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:37:33 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/02 10:32:13 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*creat_env_node(t_gc *gc, char *env)
{
	char	*equal_pos;
	size_t	key_len;
	t_env	*new_node;

	equal_pos = ft_strchr(env, '=');
	if (!equal_pos)
		return (NULL);
	key_len = equal_pos - env;
	new_node = gc_malloc(gc, sizeof(t_env), 0);
	if (!new_node)
		return (NULL);
	new_node->key = gc_strndup(gc, env, key_len);
	new_node->value = gc_strdup(gc, equal_pos + 1);
	new_node->next = NULL;
	if (!ft_strcmp(new_node->value, ""))
		return (NULL);
	return (new_node);
}

t_env	*fill_env(t_gc *gc, char **envp)
{
	t_env	*head;
	t_env	*current;
	int		i;
	t_env	*new_node;

	i = 0;
	head = NULL;
	current = NULL;
	while (envp[i])
	{
		new_node = creat_env_node(gc, envp[i]);
		if (!new_node)
		{
			i++;
			continue ;
		}
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}
