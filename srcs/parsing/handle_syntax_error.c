/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:20:58 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/16 14:54:23 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_unclosed_quotes(char *str)
{
	int i;
	int is_single_quote;
	int is_double_quote;

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
		printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	handle_some_of_unexpected_token(t_token *current)
{
	// t_token	*top;

	// top = current;
	if ((current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == HEREDOC || current->type == APPEND)
		&& current->next && current->next->type != WORD)
	{
		ft_printf(2, "syntax error near unexpected token `%s'\n",
			current->next->str);
		return (1);
	}
	if ((current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == HEREDOC || current->type == APPEND)
		&& (!current->next || current->next->type != WORD))
	{
		ft_printf(2, "syntax error near unexpected token `newline'\n");
		return (1);
	}
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
			ft_printf(2, "syntax error near unexpected token `newline'\n");
			return (1);
		}
		if (current->type == PIPE && !current->next)
		{
			ft_printf(2, "syntax error near unexpected token `|'\n");
			return (1);
		}
		if (handle_some_of_unexpected_token(current))
			return (1);
		if (top->type == PIPE)
			return (ft_printf(2, "syntax error near unexpected token `|'\n"), 1);
		current = current->next;
	}
	return (0);
}
