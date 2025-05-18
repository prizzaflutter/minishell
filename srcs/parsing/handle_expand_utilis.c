/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_utilis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:39:18 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/18 20:37:05 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_varenv_value(char *var, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, var) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

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
		len++;
		(*i)++;
	}
	return (len);
}

void	initial_struct_compute_lenght(t_gc *gc, t_compute_length **cl)
{
	*cl = gc_malloc(gc, sizeof(t_compute_length), 0);
	(*cl)->i = 0;
	(*cl)->len = 0;
	(*cl)->is_sq = 0;
	(*cl)->is_dq = 0;
}

int	compute_expanded_length(t_gc *gc, char *str, t_env *env)
{
	t_compute_length	*cl;

	initial_struct_compute_lenght(gc, &cl);
	while (str[cl->i])
	{
		if (check_quote_expand(&str[cl->i], &cl->is_sq, &cl->is_dq) == 1)
			cl->i++;
		else if (str[cl->i] == '$' && !cl->is_sq)
		{
			cl->i++;
			if (!str[cl->i])
			{
				cl->len++;
				break ;
			}
			else
				cl->len += the_main_compute_lenght(gc, str, &cl->i, env);
		}
		else
		{
			cl->len++;
			cl->i++;
		}
	}
	return (cl->len);
}
