/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:56:43 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/20 12:56:44 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env(t_env **env, char *arg_key){
	t_env	*current;
	t_env	*prev;
	t_env	*next;

	current = *env;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (ft_strcmp(current->key, arg_key) == 0)
		{
			if (prev)
				prev->next = next;
			else
				*env = next;
			if (current->key)
				free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			break ;
		}
		else 
			prev = current;
		current = next;
	}
}

void	my_unset(t_env **env, char **argv)
{
	int	i;

	i = 1;
	if (!argv || !*argv)
		return;
	while(argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			printf("unset: `%s`: not a valid identifier\n", argv[i]);
			i++;
			continue;
		}
		remove_env(env, argv[i]);
		i++;
	}
}
