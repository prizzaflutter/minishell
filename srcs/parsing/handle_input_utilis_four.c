/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_utilis_four.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:52:53 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/03 17:55:25 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	detect_separator_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
		{
			i++;
			if (str[i] == '=')
				return (1);
		}
		if (str[i] == '=')
			return (2);
		i++;
	}
	return (0);
}

char	*expand_split_first_var(t_gc *gc, char *str, t_env *env)
{
	char	**new_sp;
	char	*new_str;
	char	**sp;

	new_str = gc_strdup(gc, str);
	if (detect_separator_expand(str) == 2)
		sp = gc_split(gc, str, '=');
	else if (detect_separator_expand(str) == 1)
	{
		sp = gc_split(gc, str, '=');
		sp[0] = ft_substr(gc, sp[0], 0, ft_strlen(sp[0]) - 1);
	}
	if (sp[0] && its_have_dollar_signe(sp[0])
		&& !detect_dollar_sign_insquote(sp[0]))
	{
		sp[0] = handle_expand(gc, sp[0], env);
		new_sp = gc_split(gc, sp[0], ' ');
		sp[0] = gc_strdup(gc, new_sp[count_word_test(sp[0], ' ') - 1]);
	}
	if (detect_separator_expand(str) == 2)
	{
		sp[0] = gc_strjoin(gc, sp[0], "=");
		new_str = gc_strjoin(gc, sp[0], sp[1]);
	}
	else if (detect_separator_expand(str) == 1)
	{
		sp[0] = gc_strjoin(gc, sp[0], "+");
		sp[0] = gc_strjoin(gc, sp[0], "=");
		new_str = gc_strjoin(gc, sp[0], sp[1]);
	}
	return (new_str);
}
