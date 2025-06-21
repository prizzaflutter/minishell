/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:30:25 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/21 19:46:04 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_path(t_env *env, t_gc *gc, char *path)
{
	int		check;
	char	*append;
	t_env	*curr;

	check = 0;
	append = NULL;
	curr = env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, "PWD"))
		{
			if (check == 0)
			{
				path = gc_strjoin(gc, "/", path);
				check = 1;
			}
			append = gc_strjoin(gc, curr->value, path);
			break ;
		}
		curr = curr->next;
	}
	return (append);
}

char	*normalize_path(t_env *env, t_gc *gc, char *path)
{
	char	*appended;

	appended = append_path(env, gc, path);
	return (appended);
}
