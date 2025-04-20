/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:04:38 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/20 12:41:06 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_key_value(t_gc *gc, t_env **env, char *arg)
{
	char	*key;
	char	*value;
	char	**key_value;
	
	key_value = split_key_value(gc, arg);
	if (key_value)
	{
		key = key_value[0];
		value = key_value[1];
	}
	else
	{
		key = gc_strdup(gc, arg);
		value = NULL;
	}
	if (!is_valid_identifier(key))
	{
		printf("export: `%s%s`: not a valid identifier\n", key, value);
		return ;
	}
	update_value(key, value, env, gc);
}

void	my_export(t_gc *gc, t_env **env, char **cmd_args)
{
	int	i;

	i = 1;
	if (!cmd_args[1])
		return (no_args(env));
	while(cmd_args[i])
	{
		fill_key_value(gc, env, cmd_args[i]);
		i++;
	}
}
