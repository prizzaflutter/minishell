/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:35:25 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/11 17:42:10 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

#include <minishell.h>

char	*add_space_inputs(char *str)
{
	int		i;
	int		j;
	int		len;
	int		cm;
	char	*new_str;
	int		is_quote;
	char	quote_char;

	i = 0;
	j = 0;
	cm = 0;
	is_quote = 0;
	quote_char = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !is_quote)
		{
			is_quote = 1;
			quote_char = str[i];
		}
		else if (str[i] == quote_char && is_quote)
		{
			is_quote = 0;
			quote_char = 0;
		}
		else if (!is_quote)
		{
			if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
			{
				cm++;
				i+=2;
			}
			else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
				cm++;
		}
			i++;
	}
	
	new_str = malloc(sizeof(char) * (len + (cm * 2) + 1));
	if (!new_str)
		return(printf ("Error alloc"), NULL);
	i = 0;
	j = 0;
	is_quote = 0;
	quote_char = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !is_quote)
		{
			is_quote = 1;
			quote_char = str[i];
			new_str[j++] = str[i++];
		}
		else if (str[i] == quote_char && is_quote)
		{
			is_quote = 0;
			quote_char = 0;
			new_str[j++] = str[i++];
		}
		else if ((str[i] == '>' && str[i + 1] == '>') && !is_quote)
		{
			new_str[j++] = ' ';
			new_str[j++] = str[i++];
			new_str[j++] = str[i++];
			new_str[j++] = ' ';
		}
		else if ((str[i] == '<' && str[i + 1] == '<') && !is_quote)
		{
			new_str[j++] = ' ';
			new_str[j++] = str[i++];
			new_str[j++] = str[i++];
			new_str[j++] = ' ';
		}
		else if ((str[i] == '|' || str[i] == '>' || str[i] == '<') && !is_quote)
		{
			new_str[j++] = ' ';
			new_str[j++] = str[i++];
			new_str[j++] = ' ';
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}



// int main()
// {
// 	char *new_str = add_space_inputs("echo \"hel 'test' lo\" | grep 'hi' > file.txt");
// 	printf("New string: %s\n", new_str);
// 	free(new_str);
// 	return 0;
// }
