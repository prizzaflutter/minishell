/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_expand_utilis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:56:39 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/02 10:54:06 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inistiall_struct_count_w_expand(t_count_w_expand *cw)
{
	(*cw).i = 0;
	(*cw).cm = 0;
	(*cw).quote_char = 0;
}

int	count_words_expand(const char *s)
{
	t_count_w_expand	t;

	inistiall_struct_count_w_expand(&t);
	while (s[t.i])
	{
		while (s[t.i] == ' ')
			t.i++;
		if (!s[t.i])
			break ;
		t.cm++;
		if (s[t.i] == '\'' || s[t.i] == '"')
		{
			t.quote_char = s[t.i++];
			while (s[t.i] && s[t.i] != t.quote_char)
				t.i++;
			if (s[t.i] == t.quote_char)
				t.i++;
		}
		else
		{
			while (s[t.i] && s[t.i] != ' ' && s[t.i] != '\'' && s[t.i] != '"')
				t.i++;
		}
	}
	return (t.cm);
}
