/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:22:20 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/11 18:23:45 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

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

char	*ft_strcpy(char const *str, char charset)
{
	int		i;
	int		len;
	char	*res;
	char	quote_char;

	i = 0;
	len = 0;
	quote_char = 0;
	while (str[len] != '\0' && (quote_char || str[len] != charset))
    {
        if (!quote_char && (str[len] == '"' || str[len] == '\''))
        {
            quote_char = str[len++];
            while (str[len] != '\0' && str[len] != quote_char)
                len++;
            if (str[len] == quote_char)
                len++;
            quote_char = 0;
        }
        else
            len++;
    }
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
	char	quote_char;

	i = 0;
	j = 0;
	quote_char = 0;
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
		while (s[i] != '\0' && (quote_char || s[i] != c))
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
	}
	strings[j] = NULL;
	return (strings);
}

int count_words(char const *str, char charset)
{
    int count = 0;
    int in_word = 0;
    char quote_char = 0;
    int i = 0;

    while (str[i])
    {
        if (!in_word && str[i] != charset)
        {
            count++;
            in_word = 1;
        }
        if (in_word && (str[i] == '"' || str[i] == '\''))
        {
            if (!quote_char)
                quote_char = str[i];
            else if (quote_char == str[i])
                quote_char = 0;
            i++;
        }
        else if (in_word && quote_char)
            i++;
        else if (in_word && str[i] == charset)
        {
            in_word = 0;
            i++;
        }
        else
            i++;
    }
    return (count);
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
	if (!strings)
	{
		free(strings);
		return (NULL);
	}
	return (strings);
}
		
int main()
{
	char *str = "aaaaa 'worldthis' is \"a test\" aaaa'qwertyui' string";
	char **result = ft_split(str, ' ');
	int i = 0;
	while (result[i])
	{
		printf("word[%d]: %s\n", i+1, result[i]);
		i++;
	}
}