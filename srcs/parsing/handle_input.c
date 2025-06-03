/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:14:22 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/02 15:30:23 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_when_dollarsign_bf_exp(t_gc *gc, t_token **tokens,
		char *str, t_env *env)
{
	char	*new_str;
	char	**char_tmp;
	int		i;

	new_str = handle_expand(gc, str, env);
	new_str = handle_double_single_quotes(gc, new_str);
	char_tmp = ft_split(gc, new_str);
	i = 0;
	while (char_tmp[i])
	{
		add_element_to_tokens(gc, tokens, char_tmp[i]);
		i++;
	}
}

void	assistant_all_the_work(t_gc *gc, t_token **tokens, t_env *env,
	t_token *tmp)
{
	if (tmp->prev && ft_strcmp(tmp->prev->str, "echo") == 0)
		handle_echo_expand_element(gc, tokens, env, tmp->str);
	else if (its_have_dollar_signe(tmp->str))
		handle_expand_dollar_sign(gc, tokens, env, tmp->str);
	else if (tmp->prev && (tmp->prev->type == REDIR_IN
			|| tmp->prev->type == REDIR_OUT || tmp->prev->type == APPEND))
		handle_val_before_addtokens(gc, tokens, tmp->str);
	else
		handle_val_before_addtokens(gc, tokens, tmp->str);
}

int	compare_detect_condition(char *new_str)
{
	if ((ft_strncmp(new_str, "<", 1) == 0)
		|| (ft_strncmp(new_str, ">", 1) == 0)
		|| (ft_strncmp(new_str, ">>", 2) == 0)
		|| (ft_strncmp(new_str, "<<", 2) == 0)
		|| (ft_strncmp(new_str, "|", 1) == 0))
		return (1);
	return (0);
}

void	all_the_work(t_gc *gc, t_token **tokens, t_env *env, t_token *tmp)
{
	t_str_inputs	*instr;
	t_token			*new_token;
	char			*new_str;

	new_str = handle_double_single_quotes(gc, tmp->str);
	instr = gc_malloc(gc, sizeof(t_str_inputs), 0);
	if (tmp && (ft_strcmp(tmp->str, "echo") == 0))
		instr->echo_str = gc_strdup(gc, tmp->str);
	if (tmp->prev && tmp->prev->prev && its_have_dollar_signe(tmp->str)
		&& (ft_strcmp(tmp->prev->str, "export") == 0)
		&& its_have_dollar_signe(tmp->prev->prev->str))
		split_when_dollarsign_bf_exp(gc, tokens, tmp->str, env);
	else if (tmp->prev && (ft_strcmp(tmp->prev->str, "export") == 0)
		&& its_have_dollar_signe(tmp->str))
	{
		initia_str_value(gc, &instr, tmp->str, tmp->prev->str);
		handle_expand_dollar_sign_export(gc, tokens, env, instr);
	}
	else if (compare_detect_condition(new_str) && instr->echo_str)
	{
		new_token = ft_lstnew(gc, new_str, 1, 1);
		ft_lstadd_back(tokens, new_token);
	}
	else
		assistant_all_the_work(gc, tokens, env, tmp);
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
