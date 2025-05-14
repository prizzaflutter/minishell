/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:56:43 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/13 11:46:26 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_current_node(t_env	*node)
// {
// 	// if (node->key)
// 	// 	free(node->key);
// 	// if (node->value)
// 	// 	free(node->value);
// 	free(node);
// }

void	remove_env(t_env **env, char *arg_key)
{
	t_env	*current;
	t_env	*prev;

	if (!env || !*env)
	{
		printf("env is null in remove env unset\n");
		return ;
	}
	current = *env;
	prev = NULL;
	while (current)
	{
		if (current->key && !ft_strcmp(current->key, arg_key))
		{
			if (prev)
			{
				printf("prev != null\n");
				prev->next = current->next;
			}
			else
			{
				printf("removing head nod\n");
				**env = *current->next;
			}
			break ;
		}
		prev = current;
		current = current->next;
	}
}


void	my_unset(t_env **env, char **argv)
{
	int	i;

	i = 1;
	if (!env || !*env || !argv || !*argv)
		return ;
	while (argv[i])
	{
		remove_env(env, argv[i]);
		i++;
	}
}
