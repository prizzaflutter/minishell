/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_old_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:58:59 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/20 17:15:36 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd(t_gc *gc, t_env *env, char *oldpwd)
{
	int		is_exist;
	char	**key_value;

	is_exist = 0;
	while (env)
	{
		if (!ft_strcmp(env->key, "OLDPWD"))
		{
			if (env->value)
			{
				env->value = oldpwd;
				is_exist = 1;
			}
			break ;
		}
		env = env->next;
	}
	if (!is_exist && oldpwd)
	{
		key_value = gc_malloc(gc, 3 * sizeof(char *), 0);
		key_value[0] = gc_strdup(gc, "");
		key_value[1] = gc_strjoin(gc, "OLDPWD=", oldpwd);
		key_value[2] = NULL;
		my_export(gc, &env, key_value, 0);
	}
}
