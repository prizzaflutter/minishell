/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:37:33 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/22 17:15:57 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*fill_env(t_gc *gc, char **envp)
{
	t_env	*head;
	t_env	*current;
	int		i;
	char 	*equal_pos;
	
	i = 0;
	head = NULL;
	current = NULL;
	while (envp[i])
	{
		equal_pos = ft_strchr(envp[i], '=');
		if (!equal_pos)
		{
			i++;
			continue;
		}
		size_t key_len = equal_pos - envp[i];
		t_env *new_node = gc_malloc(gc, sizeof(t_env), 0);
		if (!new_node)
			return NULL;
		new_node->key = gc_strndup(gc, envp[i], key_len);
		new_node->value = gc_strdup(gc, equal_pos + 1);
		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return head;
}