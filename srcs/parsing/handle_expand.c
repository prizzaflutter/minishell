/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:53:28 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/15 11:20:34 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int detect_quotes(const char *str)
// {
//     int		i;
//     int		quote_state;  // 0 = unquoted, 1 = double quote, 2 = single quote
//     char	quote_char;

// 	i = 0;
// 	quote_state = 0;
// 	quote_char = 0;
//     while (str[i])
//     {
//         if ((str[i] == '"' || str[i] == '\'') && quote_state == 0)
//         {
// 			if (str[i] == '"')
// 				quote_state = 1;
// 			else
// 				quote_state = 2;
// 			quote_char = str[i];
//         }
//         else if (str[i] == quote_char && quote_state != 0)
//         {
//             quote_state = 0;
//             quote_char = 0;
//         }
//         else if (str[i] == '$')
//             return (quote_state);
//         i++;
//     }
//     return quote_state;
// }

// char	*expand_variable(char *str)
// {
// 	char	*res;
// 	int		i;
// 	int		j;
// 	int		len;

// 	if(!str)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] && str[i] != '$')
// 		i++;
// 	if (str[i] == '$')
// 	{
// 		i++;
// 		j = i;
// 		while (str[j] && (isalnum(str[j]) || str[j] == '_'))
// 			j++;
// 		len = j - i;
// 		res = malloc(sizeof(char) * (len + 1));
// 		if (!res)
// 			return (NULL);
// 		strncpy(res, str + i, len);
// 		res[len] = '\0';
// 	}
// 	else
// 		res = strdup(str);
// 	return (res);
// }

// char *handle_expand(char *str)
// {
// 	char	*res;
// 	int		len;
// 	char	*env_tmp;
// 	int		i;
// 	int		j;
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] && str[i] != '$' && str[i] != '"' && str[i] != '\'')
// 	env_tmp = expand_variable(str);
// 	if (!env_tmp)
// 		return (NULL);
// 	return (res);
// }

char *ft_strjoin_char(char *s1, char c)
{
	char	*res;
	int		i;

	if (!s1 || !c)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = '\0';
	return (res);
}

char *handle_expand(char *str)
{
	char	*res = ft_strdup("");
	int		i;
	int		is_single_quote;
	int		is_double_quote;
	char	*env_tmp;
	char	*new_str;

	i = 0;
	is_single_quote = 0;
	is_double_quote = 0;
	while (str[i])
	{
		if (str[i] == '"' && !is_single_quote)
		{
			is_double_quote = !is_double_quote;
			i++;
		}
		else if (str[i] == '\'' && !is_double_quote)
		{
			is_single_quote = !is_single_quote;
			i++;
		}
		else if (str[i] == '$' && !is_single_quote)
		{
			i++;
			int j = i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			env_tmp = ft_substr(str,j, i - j);
			new_str = ft_strjoin(res, getenv(env_tmp));
			free(env_tmp);
			if (!res)
				return (NULL);
			free(res);
			res	= new_str;
		}
		else
		{
			new_str = ft_strjoin_char(res, str[i]);
			if (!res)
				return (NULL);
			free(res);
			res = new_str;
			i++;
		}
	}
	return (res);
}


// int main(int argc, char **argv)
// {
// 	char *str = "aaaaa'$USER'aaaaa";
// 	char *res;

// 	printf("the value is .%s.\n", handle_expand(str));
// }

	