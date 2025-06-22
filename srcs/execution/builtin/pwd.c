/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:26:00 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/22 09:28:07 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_pwd(t_env *env)
{
	char	content[4096];
	char	*cwd;

	cwd = getcwd(content, sizeof(content));
	if (cwd)
	{
		printf("%s\n", content);
		return ;
	}
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD"))
		{
			if (env->value)
				printf("%s\n", env->value);
			break ;
		}
		env = env->next;
	}
}
