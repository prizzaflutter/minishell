/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:43:26 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/13 10:45:42 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_pwd(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD"))
			printf("%s\n", env->value);
		env = env->next;
	}
}
