/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:22:20 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/09 11:22:31 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strings(char **strings)
{
	int	j;

	j = 0;
	if (!strings)
		return ;
	while (strings[j])
	{
		free(strings[j]);
		j++;
	}
	free(strings);
}

int	count_words(char const *str, char charset)
{
	int	i;
	int	cm;

	cm = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == charset)
			i++;
		if (str[i] != '\0')
			cm++;
		while (str[i] != '\0' && str[i] != charset)
			i++;
	}
	return (cm);
}

char	*ft_strcpy(char const *str, char charset)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = 0;
	while (str[len] != '\0' && str[len] != charset)
		len++;
	res = malloc(len + 1);
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

char	**allwork(char **strings, char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			strings[j] = ft_strcpy(&s[i], c);
			if (!strings[j])
			{
				free_strings(strings);
				return (NULL);
			}
			j++;
		}
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	strings[j] = NULL;
	return (strings);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;

	if (!s)
		return (NULL);
	strings = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!strings)
		return (NULL);
	strings = allwork(strings, s, c);
	return (strings);
}