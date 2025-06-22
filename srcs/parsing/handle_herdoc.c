/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:10:16 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/22 15:26:16 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_len_delimeter(char *str)
{
	int		i;
	int		len;
	t_quote	quote;

	quote.is_quote = 0;
	quote.quote_char = 0;
	i = 0;
	len = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !quote.is_quote)
		{
			quote.is_quote = 1;
			quote.quote_char = str[i];
		}
		else if (str[i] == quote.quote_char && quote.is_quote)
		{
			quote.is_quote = 0;
			quote.quote_char = 0;
		}
		else
			len++;
		i++;
	}
	return (len);
}

int	quotes_detect(char str, t_quote **quote)
{
	if ((str == '"' || str == '\'') && !(*quote)->is_quote)
	{
		(*quote)->is_quote = 1;
		(*quote)->quote_char = str;
		return (1);
	}
	else if (str == (*quote)->quote_char && (*quote)->is_quote)
	{
		(*quote)->is_quote = 0;
		(*quote)->quote_char = 0;
		return (1);
	}
	return (0);
}

char	*handle_delemitre(t_gc *gc, char *str)
{
	int		i;
	int		j;
	char	*new_str;
	t_quote	*quote;

	quote = gc_malloc(gc, sizeof(t_quote), 0);
	if (!quote)
		return (NULL);
	quote->is_quote = 0;
	quote->quote_char = 0;
	new_str = gc_malloc(gc, sizeof(char)
			* (count_len_delimeter(str) + 1), 0);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (quotes_detect(str[i], &quote))
			i++;
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

int	handle_herdocs(t_gc *gc, t_token *t_token, t_env *env)
{
	int	fd;
	int	tmp;

	fd = -2;
	while (t_token)
	{
		if (t_token->type == HEREDOC && t_token->next
			&& t_token->next->type == WORD)
		{
			fd = handle_herdoc_input(gc, t_token->next->str, t_token, env);
			if (fd != -2 && tmp)
				close(tmp);
			tmp = fd;
			if (fd < 0)
				return (-1);
			t_token = t_token->next;
		}
		t_token = t_token->next;
	}
	return (fd);
}
