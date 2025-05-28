/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:47:32 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/28 16:00:11 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_expand_env_var(t_gc *gc, char *str, int *i, t_env *env)
{
	char	*varname;
	char	*varvalue;
	int		j;
	int		len;

	len = 0;
	j = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	varname = ft_substr(gc, str, j, *i - j);
	varvalue = get_varenv_value(varname, env);
	if (varvalue)
		len += ft_strlen(varvalue);
	return (len);
}

int	the_main_compute_lenght(t_gc *gc, char *str, int *i, t_env *env)
{
	int		len;

	len = 0;
	if (str[*i] == '$')
	{
		len++;
		(*i)++;
	}
	else if (str[*i] == '?')
	{
		len += ft_strlen(ft_itoa(gc, exit_status(0, 0)));
		(*i)++;
	}
	else if (str[*i] && (ft_isalpha(str[*i]) || str[*i] == '_'))
		len += count_expand_env_var(gc, str, i, env);
	else
	{
		len += 2;
		(*i)++;
	}
	return (len);
}

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

void	initial_struct_handle_expand(t_gc *gc, t_var_expand	**vx, int is_her)
{
	*vx = gc_malloc(gc, sizeof(t_var_expand), 0);
	(*vx)->i = 0;
	(*vx)->k = 0;
	(*vx)->is_squote = 0;
	(*vx)->is_dquote = 0;
	(*vx)->is_her = is_her;
}

char	*handle_expand_herdoc(t_gc *gc, char *str, int flag, t_env *env)
{
	t_var_expand	*vx;

	initial_struct_handle_expand(gc, &vx, 1);
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
