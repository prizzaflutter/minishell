/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:55:46 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/31 17:41:10 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	the_new_len_expand(char const *s)
{
	int		i;
	char	quote_char;

	i = 0;
	quote_char = 0;
	
	if (s[i] == '"' || s[i] == '\'')
	{
		quote_char = s[i++];
		while (s[i] != '\0' && s[i] != quote_char)
			i++;
		if (s[i] == quote_char)
			i++;
		return (i);
	}
	else
	{
		while (s[i] && s[i] != ' ' && s[i] != '\'' && s[i] != '"')
			i++;
		return (i);
	}
}

char	*ft_strcpy_expand(t_gc *gc, char const *str)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	printf("count >>> %d\n",the_new_len_expand(str));
	len = the_new_len_expand(str);
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

char	**allwork_expand(t_gc *gc, char **strings, char const *s)
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
			strings[j] = ft_strcpy_expand(gc, &s[i]);
			printf("strings >> %s\n",strings[j]);
			if (!strings[j])
				return (NULL);
			j++;
		}
		i += the_new_len_expand(&s[i]);
	}
	strings[j] = NULL;
	return (strings);
}

char	**ft_split_expand(t_gc *gc, char const *s)
{
	char	**strings;

	if (!s)
		return (NULL);
	strings = (char **)gc_malloc(gc, (count_words_expand(s) + 1) * sizeof(char *), 0);
	if (!strings)
		return (NULL);
	strings = allwork_expand(gc, strings, s);
	if (!strings)
		return (NULL);
	return (strings);
}


// static int	count_words_expand(char const *str)
// {
// 	int	i;
// 	int	cm;

// 	cm = 0;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		while (str[i] != '\0' && (str[i] == '"' || str[i] == '\''))
// 			i++;
// 		if (str[i] != '\0')
// 			cm++;
// 		while (str[i] != '\0' && str[i] != '"' && str[i] != '\'')
// 			i++;
// 	}
// 	return (cm);
// }

// static char	*ft_strcpy_expand(t_gc *gc, char const *str)
// {
// 	int		i;
// 	int		len;
// 	char	*res;

// 	i = 0;
// 	len = 0;
// 	while (str[len] != '\0' && str[i] != '"' && str[i] != '\'')
// 		len++;
// 	res = gc_malloc(gc ,len + 1, 0);
// 	if (!res)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		res[i] = str[i];
// 		i++;
// 	}
// 	res[i] = '\0';
// 	return (res);
// }

// static char	**allwork_expand(t_gc *gc, char **strings, char const *s)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (s[i] != '\0')
// 	{
// 		while (s[i] != '\0' && (s[i] == '"' || s[i] == '\''))
// 			i++;
// 		if (s[i] != '\0')
// 		{
// 			strings[j] = ft_strcpy_expand(gc, &s[i]);
// 			if (!strings[j])
// 				return (NULL);
// 			j++;
// 		}
// 		while (s[i] != '\0' && s[i] != '"' && s[i] != '\'')
// 			i++;
// 	}
// 	strings[j] = NULL;
// 	return (strings);
// }

// char	**ft_split_expand(t_gc *gc, char const *s)
// {
// 	char	**strings;

// 	if (!s)
// 		return (NULL);
// 	strings = (char **)gc_malloc(gc ,(count_words_expand(s) + 1) * sizeof(char *), 0);
// 	if (!strings)
// 		return (NULL);
// 	strings = allwork_expand(gc, strings, s);
// 	return (strings);
// }