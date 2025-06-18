/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:53:28 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/18 15:33:45 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote_expand(char *str, int *is_squote, int *is_dquote)
{
	if (*str == '"' && !*is_squote)
	{
		*is_dquote = !*is_dquote;
		return (1);
	}
	else if (*str == '\'' && !*is_dquote)
	{
		*is_squote = !*is_squote;
		return (1);
	}
	return (0);
}

void	expand_env_var(t_gc *gc, t_env *env, char *str, t_var_expand **vx)
{
	char	*env_tmp;
	char	*new_str;
	int		j;

	j = (*vx)->i;
	while (str[(*vx)->i] && (ft_isalnum(str[(*vx)->i])
			|| str[(*vx)->i] == '_'))
		(*vx)->i++;
	env_tmp = ft_substr(gc, str, j, (*vx)->i - j);
	new_str = get_varenv_value(env_tmp, env);
	j = 0;
	while (new_str && new_str[j])
		(*vx)->res[(*vx)->k++] = new_str[j++];
}

void	expand_exit_status(t_gc *gc, t_var_expand **vx)
{
	char	*nbr;
	int		j;

	j = 0;
	nbr = ft_itoa(gc, exit_status(0, 0));
	while (nbr[j])
		(*vx)->res[(*vx)->k++] = nbr[j++];
	(*vx)->i++;
}

void	the_main_expand(t_gc *gc, t_env *env, char *str, t_var_expand **vx)
{
	if (str[(*vx)->i] && str[(*vx)->i] == '$')
	{
		(*vx)->res[(*vx)->k++] = '$';
		(*vx)->i++;
	}
	else if (str[(*vx)->i] == '?')
		expand_exit_status(gc, vx);
	else if (ft_isdigit(str[(*vx)->i]) || str[(*vx)->i] == '@')
		(*vx)->i++;
	else if (str[(*vx)->i] && (ft_isalpha(str[(*vx)->i])
			|| str[(*vx)->i] == '_'))
		expand_env_var(gc, env, str, vx);
	else
	{
		if (!(*vx)->is_her)
			(*vx)->res[(*vx)->k++] = '$';
		(*vx)->res[(*vx)->k++] = str[(*vx)->i++];
	}
}

char	*handle_expand(t_gc *gc, char *str, t_env *env)
{
	t_var_expand	*vx;	

	initial_struct_handle_expand(gc, &vx, 0);
	vx->res = gc_malloc(gc, sizeof (char)
			* (compute_expanded_length(gc, str, env) + 1), 0);
	while (str[vx->i])
	{
		if (check_quote_expand(&str[vx->i],
				&vx->is_squote, &vx->is_dquote) == 1)
			vx->res[vx->k++] = str[vx->i++];
		else if (str[vx->i] == '$' && !vx->is_squote)
		{
			vx->i++;
			if (!str[vx->i])
			{
				vx->res[vx->k++] = '$';
				break ;
			}
			else
				the_main_expand(gc, env, str, &vx);
		}
		else
			vx->res[vx->k++] = str[vx->i++];
	}
	return (vx->res[vx->k] = '\0', vx->res);
}
