/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:43:26 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/19 10:50:27 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_pwd(t_env *env)
{
	char	content[4096];
	char	*cwd;
	
	cwd = getcwd(content, sizeof(content));
	if (cwd)
		printf("%s\n", content);
	else
	{
		while (env)
		{
			if (!ft_strcmp(env->key, "PWD"))
				printf("%s\n", env->value);
			env = env->next;
		}
	}
}
