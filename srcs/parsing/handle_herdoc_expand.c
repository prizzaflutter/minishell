/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:47:32 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/18 20:48:57 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compute_expanded_length_herdoc(t_gc *gc, char *str, int flag, t_env *env)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$' && flag == 0)
		{
			i++;
			len += the_main_compute_lenght(gc, str, &i, env);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*handle_expand_herdoc(t_gc *gc, char *str, int flag, t_env *env)
{
	t_var_expand	*vx;

	initial_struct_handle_expand(gc, &vx);
	vx->res = gc_malloc(gc, sizeof(char)
			* (compute_expanded_length_herdoc(gc, str, flag, env) + 1), 0);
	if (flag == 0)
	{
		while (str[vx->i])
		{
			if (str[vx->i] == '$')
			{
				vx->i++;
				the_main_expand(gc, env, str, &vx);
			}
			else
				vx->res[vx->k++] = str[vx->i++];
		}
	}
	else
		return (gc_strdup(gc, str));
	vx->res[vx->k] = '\0';
	return (vx->res);
}
