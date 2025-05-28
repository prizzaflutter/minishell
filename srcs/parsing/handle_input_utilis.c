/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_utilis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:03:55 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/28 13:21:14 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	its_have_dollar_signe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	count_length_without_quotes(char *str)
{
	int		i;
	int		count;
	int		is_quote;
	char	quote_char;

	i = 0;
	count = 0;
	is_quote = 0;
	quote_char = 0;
	while (str[i])
	{
		if (check_quote(&str[i], &is_quote, &quote_char) != 0)
		{
			i++;
			continue ;
		}
		else
			count++;
		i++;
	}
	return (count);
}

char	*handle_double_single_quotes(t_gc *gc, char *str)
{
	char	*new_str;
	int		is_quote;
	char	quote_char;
	int		i;
	int		j;

	i = 0;
	j = 0;
	is_quote = 0;
	quote_char = 0;
	new_str = gc_malloc(gc, sizeof(char)
			* (count_length_without_quotes(str) + 1), 0);
	while (str[i])
	{
		if (check_quote(&str[i], &is_quote, &quote_char) != 0)
		{
			i++;
			continue ;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}
