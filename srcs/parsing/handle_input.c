/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:14:22 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/22 20:22:50 by aykassim         ###   ########.fr       */
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
	if (its_have_dollar_signe(tmp->str))
		handle_expand_dollar_sign(gc, tokens, env, tmp->str);
	else
		handle_val_before_addtokens(gc, tokens, tmp->str);
}

void	handle_all_export_val(t_gc *gc, t_token **tokens,
	t_env *env, t_token **tmp)
{
	t_token			*cur;
	int				count;
	int				i;
	t_str_inputs	*ins;

	ins = gc_malloc(gc, sizeof(t_str_inputs), 0);
	count = detect_nombre_export_value(*tmp);
	i = 0;
	cur = *tmp;
	while (i < count)
	{
		(*tmp) = (*tmp)->next;
		if (cur->prev && its_have_dollar_signe((*tmp)->str)
			&& its_have_dollar_signe(cur->prev->str))
			split_when_dollarsign_bf_exp(gc, tokens, (*tmp)->str, env);
		else if (its_have_dollar_signe((*tmp)->str))
		{
			initia_str_value(gc, &ins, (*tmp)->str, cur->str);
			handle_expand_dollar_sign_export(gc, tokens, env, ins);
		}
		else
			handle_val_before_addtokens(gc, tokens, (*tmp)->str);
		i++;
	}
}

void	all_the_work(t_gc *gc, t_token **tokens, t_env *env, t_token **tmp)
{
	t_str_inputs	instr;
	t_token			*new_token;
	char			*new_str;

	new_str = handle_double_single_quotes(gc, (*tmp)->str);
	instr.exp_str = gc_strdup(gc, "");
	instr.echo_str = gc_strdup(gc, "");
	if ((*tmp) && (ft_strcmp((*tmp)->str, "echo") == 0))
		instr.echo_str = gc_strdup(gc, (*tmp)->str);
	if ((*tmp) && (ft_strcmp(new_str, "export") == 0))
		instr.exp_str = gc_strdup(gc, (*tmp)->str);
	if (compare_detect_condition(new_str) && instr.echo_str)
	{
		new_token = ft_lstnew(gc, new_str, 1, 1);
		ft_lstadd_back(tokens, new_token);
	}
	else if ((*tmp)->next && instr.echo_str
		&& !compare_detect_condition(new_str))
		handle_echo_expand_element(gc, tokens, env, (*tmp)->str);
	else if ((*tmp)->next && instr.exp_str && (*tmp)->next->type == WORD)
		return (handle_val_before_addtokens(gc, tokens, new_str),
			handle_all_export_val(gc, tokens, env, tmp));
	else
		assistant_all_the_work(gc, tokens, env, *tmp);
}

int	add_command_element(t_gc *gc, char *str, t_token **tokens, t_env *env)
{
	t_token	*tmp;

	tmp = NULL;
	add_element_to_listcopy(gc, str, &tmp);
	if (handle_unexpected_token(tmp))
		return (exit_status(1, 2), -1);
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
				all_the_work(gc, tokens, env, &tmp);
		}
		else
			add_element_to_tokens(gc, tokens, tmp->str);
		tmp = tmp->next;
	}
	return (gc_clear(gc, 4), tmp = NULL, 0);
}
