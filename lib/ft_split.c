/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:56:34 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/15 16:29:44 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	the_new_len(char const *s)
{
	int		i;
	char	quote_char;

	i = 0;
	quote_char = 0;
	while (s[i] != '\0' && (quote_char || (s[i] != ' ' && s[i] != 9)))
	{
		if (!quote_char && (s[i] == '"' || s[i] == '\''))
		{
			quote_char = s[i++];
			while (s[i] != '\0' && s[i] != quote_char)
				i++;
			if (s[i] == quote_char)
				i++;
			quote_char = 0;
		}
		else
			i++;
	}
	return (i);
}

char	*ft_strcpy(t_gc *gc, char const *str)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = the_new_len(str);
	res = gc_malloc(gc, len + 1, 0);
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	**allwork(t_gc *gc, char **strings, char const *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && (s[i] == ' ' || s[i] == 9))
			i++;
		if (s[i] != '\0')
		{
			strings[j] = ft_strcpy(gc, &s[i]);
			if (!strings[j])
				return (NULL);
			j++;
		}
		i += the_new_len(&s[i]);
	}
	strings[j] = NULL;
	return (strings);
}

char	**ft_split(t_gc *gc, char const *s)
{
	char	**strings;

	if (!s)
		return (NULL);
	strings = (char **)gc_malloc(gc, (count_words(s) + 1) * sizeof(char *), 0);
	if (!strings)
		return (NULL);
	strings = allwork(gc, strings, s);
	if (!strings)
		return (NULL);
	return (strings);
}
