/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:45:01 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/21 11:05:17 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_is_only_whitespace(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	handle_unclosed_quotes(char *str)
{
	int	i;
	int	is_single_quote;
	int	is_double_quote;

	i = 0;
	is_single_quote = 0;
	is_double_quote = 0;
	while (str[i])
	{
		if (str[i] == '"' && !is_single_quote)
			is_double_quote = !is_double_quote;
		else if (str[i] == '\'' && !is_double_quote)
			is_single_quote = !is_single_quote;
		i++;
	}
	if (is_single_quote || is_double_quote)
	{
		ft_printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	handle_some_of_unexpected_token(t_token *current)
{
	if ((current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == HEREDOC || current->type == APPEND)
		&& current->next && current->next->type != WORD)
	{
		ft_printf("syntax error near unexpected token `%s'\n",
			current->next->str);
		return (1);
	}
	if ((current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == HEREDOC || current->type == APPEND)
		&& (!current->next || current->next->type != WORD))
	{
		ft_printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (current->type == PIPE && current->next && current->next->type == PIPE)
		return (ft_printf("syntax error near unexpected token `|'\n"), 1);
	return (0);
}

int	handle_unexpected_token(t_token *tokens)
{
	t_token	*current;
	t_token	*top;

	current = tokens;
	top = current;
	while (current)
	{
		if (current->type == REDIR_IN && current->next
			&& current->next->type == REDIR_OUT)
		{
			ft_printf("syntax error near unexpected token `newline'\n");
			return (1);
		}
		if (current->type == PIPE && !current->next)
			return (ft_printf("syntax error near unexpected token `|'\n"), 1);
		if (handle_some_of_unexpected_token(current))
			return (1);
		if (top->type == PIPE)
			return (ft_printf("syntax error near unexpected token `|'\n"), 1);
		current = current->next;
	}
	return (0);
}
