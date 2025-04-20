/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:46:30 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/19 18:55:12 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_word(const char *s, char c)
{
	size_t	counter;
	int		in_word;
	int		i;

	i = 0;
	counter = 0;
	in_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && in_word == 0)
		{
			in_word = 1;
			counter++;
		}
		else if (s[i] == c && in_word == 1)
		{
			in_word = 0;
		}
		i++;
	}
	return (counter);
}

// static void	*free_split(char **s, size_t len)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		free(s[i]);
// 		i++;
// 	}
// 	free(s);
// 	return (NULL);
// }

static char	*fill_index(char *final_str, const char *start, size_t lenght)
{
	size_t	j;

	j = 0;
	while (j < lenght)
	{
		final_str[j] = start[j];
		j++;
	}
	final_str[lenght] = '\0';
	return (final_str);
}

static char	**fill_final_str(t_gc *gc, char **final_str, const char *s, char c)
{
	const char	*start;
	int			i;
	size_t		diff_length;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = s;
			while (*s && *s != c)
				s++;
			diff_length = (s - start);
			final_str[i] = (char *)ft_calloc (gc, (diff_length + 1), sizeof(char));
			if (final_str[i] == NULL)
				return (NULL);
			fill_index(final_str[i], start, diff_length);
			i++;
		}
		else
			s++;
	}
	return (final_str);
}

char	**gc_split(t_gc *gc, char const *s, char c)
{
	char	**final_str;
	size_t	len;

	if (s == NULL)
		return (NULL);
	len = count_word(s, c);
	final_str = (char **)ft_calloc(gc, (len + 1), sizeof(char *));
	if (final_str == NULL)
		return (NULL);
	return (fill_final_str(gc, final_str, s, c));
}
