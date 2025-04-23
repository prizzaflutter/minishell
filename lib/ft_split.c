#include "minishell.h"

char	*ft_strcpy(t_gc *gc,char const *str, char charset)
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

char	**allwork(t_gc *gc, char **strings, char const *s, char c)
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
			strings[j] = ft_strcpy(gc ,&s[i], c);
			if (!strings[j])
				return (NULL);
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

char	**ft_split(t_gc *gc, char const *s, char c)
{
	char	**strings;

	if (!s)
		return (NULL);
	strings = (char **)gc_malloc(gc ,(count_words(s, c) + 1) * sizeof(char *), 0);
	if (!strings)
		return (NULL);
	strings = allwork(gc ,strings, s, c);
	if (!strings)
		return (NULL);
	return (strings);
}
