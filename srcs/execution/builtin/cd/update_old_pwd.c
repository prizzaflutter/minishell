/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_old_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:58:59 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/22 15:48:37 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd(t_gc *gc, t_env **env, char *oldpwd)
{
	int		is_exist;
	char	**key_value;
	t_env	*curr;

	(1) && (is_exist = 0, curr = *env);
	while (curr)
	{
		if (!ft_strcmp(curr->key, "OLDPWD"))
		{
			if (!curr->value)
				break ;
			curr->value = oldpwd;
			is_exist = 1;
			break ;
		}
		curr = curr->next;
	}
	if (!is_exist && oldpwd)
	{
		key_value = gc_malloc(gc, 3 * sizeof(char *), 0);
		key_value[0] = gc_strdup(gc, "export");
		key_value[1] = gc_strjoin(gc, "OLDPWD=", oldpwd);
		key_value[2] = NULL;
		my_export(gc, env, key_value, 0);
	}
}
