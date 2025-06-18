/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_old_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:37:54 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/16 20:31:17 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd(t_gc *gc, t_env *env, char *oldpwd)
{
	int		is_exist;
	char	**key_value;
	t_env	*cur;

	is_exist = 0;
	cur = env;
	while (cur)
	{
		if (!ft_strcmp(cur->key, "OLDPWD"))
		{
			if (cur->value)
			{
				cur->value = oldpwd;
				is_exist = 1;
			}
			break ;
		}
		cur = cur->next;
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
