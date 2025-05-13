/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:00:44 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/13 11:06:18 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_env(t_env *env)
{
	while (env)
	{
		if (env->value && ft_strcmp(env->value, "="))
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
