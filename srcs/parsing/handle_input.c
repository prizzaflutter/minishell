/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:21:56 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/12 14:38:15 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	new_str = malloc(sizeof(char) * (len + cm * 2 + 1));
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

int define_token_type(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, "<") == 0)
		return (REDIR_IN);
	else if (strcmp(str, ">") == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(str, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(str, ">>") == 0)
		return (APPEND);
	else
		return (WORD);
}

int add_command_element(char *str, t_token **tokens)
{
	t_token	*new_token;
	char	**res;
	int i;

	if (!str || !tokens)
		return (0);
	str = add_space_inputs(str);
	if (!str)
		return (printf("Error in add_space_inputs"), 0);
	res = ft_split(str, ' ');
	if (!res)
		return (printf("Error in ft_split"), 0);
	if (!res)
		return (printf("Error in split"), 0);
	i = 0;
	while (res[i])
	{
		new_token = ft_lstnew(res[i]);
		if (!new_token)
		{
			free(res);
			return (printf("Error in token creation"), 0);
		}
		ft_lstadd_back(tokens, new_token);
		i++;
	}
	free(res);
	return (1);
}
