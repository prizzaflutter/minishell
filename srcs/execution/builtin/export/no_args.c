/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:03:38 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/15 11:50:22 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(t_copy *a, t_copy *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

t_copy	*create_copy(t_env *env, t_gc *gc)
{
	t_copy	*copy;
	t_env	*curr;
	t_copy	*new_node;

	copy = NULL;
	curr = env;
	while (curr)
	{
		new_node = ft_lstnew_copy(gc, curr->key, curr->value);
		ft_lstadd_back_copy(&copy, new_node);
		curr = curr->next;
	}
	return (copy);
}

void	sort_env(t_copy *env)
{
	t_copy	*current;
	int		is_swapped;

	is_swapped = 1;
	while (is_swapped)
	{
		is_swapped = 0;
		current = env;
		while (current && current->next)
		{
			if (ft_strcmp(current->key, current->next->key) > 0)
			{
				swap(current, current->next);
				is_swapped = 1;
			}
			current = current->next;
		}
	}
}

void	no_args(t_env *env, t_gc *gc)
{
	t_copy	*current;
	t_copy	*copy;

	copy = create_copy(env, gc);
	current = copy;
	sort_env(copy);
	while (current)
	{
		if (current->value)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("declare -x %s\n", current->key);
		current = current->next;
	}
}
