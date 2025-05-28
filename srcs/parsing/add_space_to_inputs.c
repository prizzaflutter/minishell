/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space_to_inputs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:49:02 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/28 11:41:49 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *str, int *is_quote, char *quote_char)
{
	if ((*str == '"' || *str == '\'') && !*is_quote)
	{
		*is_quote = 1;
		*quote_char = *str;
		return (2);
	}
	else if (*str == *quote_char && *is_quote)
	{
		*is_quote = 0;
		*quote_char = 0;
		return (3);
	}
	return (0);
}

int	detect_herdoc_append(char str1, char str2)
{
	if ((str1 == '<' && str2 == '<')
		|| (str1 == '>' && str2 == '>'))
	{
		return (0);
	}
	return (1);
}

int	count_word_in_inputs(char *str)
{
	int		is_quote;
	char	quote_char;
	int		i;
	int		cm;

	is_quote = 0;
	quote_char = 0;
	i = 0;
	cm = 0;
	while (str[i])
	{
		check_quote(&str[i], &is_quote, &quote_char);
		if (!is_quote)
		{
			if (!detect_herdoc_append(str[i], str[i + 1]))
			{
				cm++;
				i++;
			}
			else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
				cm++;
		}
		i++;
	}
	return (cm);
}

void	handle_new_inputs(char *str, char *new_str, t_add_space	**as)
{
	if (check_quote(&str[(*as)->i], &(*as)->isq, &(*as)->quote_char) != 0)
		new_str[(*as)->j++] = str[(*as)->i++];
	else if ((str[(*as)->i] == '>' && str[(*as)->i + 1] == '>') && !(*as)->isq)
	{
		new_str[(*as)->j++] = ' ';
		new_str[(*as)->j++] = str[(*as)->i++];
		new_str[(*as)->j++] = str[(*as)->i++];
		new_str[(*as)->j++] = ' ';
	}
	else if ((str[(*as)->i] == '<' && str[(*as)->i + 1] == '<') && !(*as)->isq)
	{
		new_str[(*as)->j++] = ' ';
		new_str[(*as)->j++] = str[(*as)->i++];
		new_str[(*as)->j++] = str[(*as)->i++];
		new_str[(*as)->j++] = ' ';
	}
	else if ((str[(*as)->i] == '|' || str[(*as)->i] == '>'
			|| str[(*as)->i] == '<') && !(*as)->isq)
	{
		new_str[(*as)->j++] = ' ';
		new_str[(*as)->j++] = str[(*as)->i++];
		new_str[(*as)->j++] = ' ';
	}
	else
		new_str[(*as)->j++] = str[(*as)->i++];
}

char	*add_space_inputs(t_gc *gc, char *str)
{
	char		*new_str;
	t_add_space	*addspace;

	addspace = gc_malloc(gc, sizeof(t_add_space), 5);
	addspace->len = ft_strlen(str);
	addspace->cm = count_word_in_inputs(str);
	new_str = gc_malloc(gc, sizeof(char)
			* (addspace->len + addspace->cm * 2 + 1), 0);
	addspace->i = 0;
	addspace->j = 0;
	addspace->isq = 0;
	addspace->quote_char = 0;
	while (str[addspace->i])
		handle_new_inputs(str, new_str, &addspace);
	new_str[addspace->j] = '\0';
	gc_clear(gc, 5);
	return (new_str);
}
