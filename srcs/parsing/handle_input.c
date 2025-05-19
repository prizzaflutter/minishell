/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:14:22 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/19 11:07:36 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_expand_dollar_sign(t_gc *gc, t_token **tokens,
	t_env *env, char *str)
{
	char	*new_str;
	char	**char_tmp;
	int		i;

	i = 0;
	new_str = handle_expand(gc, str, env);
	if (detect_quotes(new_str) == 1)
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

void	handle_expand_dollar_sign_export(t_gc *gc, t_token **tokens,
	t_env *env, t_str_inputs *ins)
{
	char	*new_str;
	char	**char_tmp;
	int		i;

	i = 0;
	new_str = handle_expand(gc, ins->str, env);
	if (detect_quotes(ins->export) != 1)
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
	t_str_inputs	*instr;

	instr = gc_malloc(gc, sizeof(t_str_inputs), 0);
	if (tmp->prev && (ft_strcmp(tmp->prev->str, "export") == 0)
		&& its_have_dollar_signe(tmp->str))
	{
		instr->export = gc_strdup(gc, tmp->prev->str);
		instr->str = gc_strdup(gc, tmp->str);
		handle_expand_dollar_sign_export(gc, tokens, env, instr);
	}
	else if (its_have_dollar_signe(tmp->str))
		handle_expand_dollar_sign(gc, tokens, env, tmp->str);
	else if (tmp->prev && ft_strcmp(tmp->prev->str, "echo") == 0)
		handle_val_before_addtokens(gc, tokens, tmp->str);
	else if (tmp->prev && (tmp->prev->type == REDIR_IN
			|| tmp->prev->type == REDIR_OUT || tmp->prev->type == APPEND))
		handle_val_before_addtokens(gc, tokens, tmp->str);
	else
		handle_val_before_addtokens(gc, tokens, tmp->str);
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
