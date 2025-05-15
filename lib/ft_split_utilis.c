/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utilis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:29:18 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/15 16:30:30 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assistant_func_cw(char const *str, int *i, int *word, char *quote_char)
{
	if (*word && (str[*i] == '"' || str[*i] == '\''))
	{
		if (!*quote_char)
			*quote_char = str[*i];
		else if (quote_char[0] == str[*i])
			*quote_char = 0;
		(*i)++;
	}
	else if (*word && *quote_char)
		(*i)++;
	else if (*word && (str[*i] == ' ' || str[*i] == 9))
	{
		*word = 0;
		(*i)++;
	}
	else
		(*i)++;
}

int	count_words(char const *str)
{
	int		cm;
	int		word;
	char	quote_char;
	int		i;

	cm = 0;
	word = 0;
	quote_char = 0;
	i = 0;
	while (str[i])
	{
		if (!word && str[i] != ' ' && str[i] != 9)
		{
			cm++;
			word = 1;
		}
		assistant_func_cw(str, &i, &word, &quote_char);
	}
	return (cm);
}
