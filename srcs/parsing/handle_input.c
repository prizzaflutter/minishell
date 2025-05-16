/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:14:22 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/16 21:16:24 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_element_to_listcopy(t_gc *gc, char *str, t_token **tokens_tmp)
{
	char	**res;
	t_token	*new_token_tmp;
	int		i;

	i = 0;
	str = add_space_inputs(gc, str);
	res = ft_split(gc, str);
	i = 0;
	while (res[i])
	{
		new_token_tmp = ft_lstnew(gc, res[i], 4);
		ft_lstadd_back(tokens_tmp, new_token_tmp);
		i++;
	}
}

void	add_element_to_tokens(t_gc *gc, t_token **tokens, char *str)
{
	t_token	*new_token;

	new_token = ft_lstnew(gc, str, 1);
	ft_lstadd_back(tokens, new_token);
}

void	handle_expand_dollar_sign(t_gc *gc, t_token **tokens,
	t_env *env, char *str)
{
	char	*new_str;
	char	**char_tmp;
	int		i;

	i = 0;
	new_str = handle_expand_generale(gc, str, detect_quotes(str, 0), env);
	if (detect_quotes(new_str, 1) == 1)
	{
		new_str = handle_double_single_quotes(gc, new_str);
		add_element_to_tokens(gc, tokens, new_str);
	}
	else
	{
		new_str = handle_double_single_quotes(gc, new_str);
		char_tmp = ft_split(gc, new_str);
		i = 0;
		while (char_tmp[i])
		{
			add_element_to_tokens(gc, tokens, char_tmp[i]);
			i++;
		}
	}
}

void	all_the_work(t_gc *gc, t_token **tokens, t_env *env, t_token *tmp)
{
	if (its_have_dollar_signe(tmp->str))
		handle_expand_dollar_sign(gc, tokens, env, tmp->str);
	else if (tmp->prev && ft_strcmp(tmp->prev->str, "echo") == 0)
	{
		tmp->str = handle_double_single_quotes(gc, tmp->str);
		add_element_to_tokens(gc, tokens, tmp->str);
	}
	else if (tmp->prev && (tmp->prev->type == REDIR_IN
			|| tmp->prev->type == REDIR_OUT || tmp->prev->type == APPEND))
	{
		tmp->str = handle_double_single_quotes(gc, tmp->str);
		add_element_to_tokens(gc, tokens, tmp->str);
	}
	///////////////tmajnin hnaaaa
	else
	{
		tmp->str = handle_double_single_quotes(gc, tmp->str);
		add_element_to_tokens(gc, tokens, tmp->str);
	}
}

int	add_command_element(t_gc *gc, char *str, t_token **tokens, t_env *env)
{
	t_token	*tmp;
	t_token	*tokens_tmp;

	tokens_tmp = NULL;
	add_element_to_listcopy(gc, str, &tokens_tmp);
	tmp = tokens_tmp;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (tmp->prev && tmp->prev->type == HEREDOC && tmp->type == WORD)
			{
				add_element_to_tokens(gc, tokens, tmp->str);
				tmp = tmp->next;
				continue ;
			}
			else
				all_the_work(gc, tokens, env, tmp);
		}
		else
			add_element_to_tokens(gc, tokens, tmp->str);
		tmp = tmp->next;
	}
	return (gc_clear(gc, 4), tokens_tmp = NULL, 0);
}
