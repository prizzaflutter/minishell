/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_utilis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:39:18 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/19 10:20:38 by aykassim         ###   ########.fr       */
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

void	initial_struct_compute_lenght(t_gc *gc, t_compute_length **cl)
{
	*cl = gc_malloc(gc, sizeof(t_compute_length), 0);
	(*cl)->i = 0;
	(*cl)->len = 0;
	(*cl)->is_sq = 0;
	(*cl)->is_dq = 0;
}

void	add_i_and_len(int *i, int *len)
{
	(*i)++;
	(*len)++;
}

int	compute_expanded_length(t_gc *gc, char *str, t_env *env)
{
	t_compute_length	*cl;

	initial_struct_compute_lenght(gc, &cl);
	while (str[cl->i])
	{
		if (check_quote_expand(&str[cl->i], &cl->is_sq, &cl->is_dq) == 1)
			add_i_and_len(&cl->i, &cl->len);
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
			add_i_and_len(&cl->i, &cl->len);
	}
	return (cl->len);
}
