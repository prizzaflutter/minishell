/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_expand_utilis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:56:39 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/31 16:06:20 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assistant_func_cw_expand(char const *str, int *i, int *word, char *quote_char)
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
	else if (*word && (str[*i] == '"' || str[*i] == '\''))
	{
		*word = 0;
		(*i)++;
	}
	else
		(*i)++;
}

// int	count_words_expand(char const *str)
// {
// 	int		cm;
// 	int		word;
// 	char	quote_char;
// 	int		i;

// 	cm = 0;
// 	word = 0;
// 	quote_char = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!word && str[i] != '"' && str[i] != '\'')
// 		{
// 			cm++;
// 			word = 1;
// 		}
// 		assistant_func_cw_expand(str, &i, &word, &quote_char);
// 	}
// 	return (cm);
// }

int	count_words_expand(const char *s)
{
	int i = 0, count = 0;
	char quote = 0;

	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break;
		count++;
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] == quote)
				i++;
		}
		else
		{
			while (s[i] && s[i] != ' ' && s[i] != '\'' && s[i] != '"')
				i++;
		}
	}
	return (count);
}
