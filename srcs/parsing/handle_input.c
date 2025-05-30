/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:14:22 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/30 15:59:33 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	detect_token_type_insquote(char *str)
{
	int		i;
	int		is_quote;
	char	quote_char;

	i = 0;
	is_quote = 0;
	quote_char = 0;
	while (str[i])
	{
		if (check_quote(str[i], &is_quote, &quote_char) != 0)
			i++;
		else if (((ft_strncmp(&str[i], "<", 1) == 0) || (ft_strncmp(&str[i], ">", 1) == 0)
				|| (ft_strncmp(&str[i], ">>", 2) == 0) || (ft_strncmp(&str[i], "<<", 2) == 0))
				&& is_quote == 1)
			return (1);
		else
			i++;
	}
	return (0);
}

int	detect_token_type_indolarsign(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((ft_strncmp(&str[i], "<", 1) == 0) || (ft_strncmp(&str[i], ">", 1) == 0)
				|| (ft_strncmp(&str[i], ">>", 2) == 0) || (ft_strncmp(&str[i], "<<", 2) == 0))
			return (1);
		else
			i++;
	}
	return (0);
}

//  void	detect_str_contain_tokns(char *str)
//  {
// 	int		i;
// 	int		is_quote;
// 	char	quote_char;

// 	i = 0;
// 	is_quote = 0;
// 	quote_char = 0;
// 	while (str[i])
// 	{
// 		if (check_quote(&str[i], &is_quote, &quote_char) != 0)
// 			i++;
// 		else if 
// 	}
//  }

void	handle_expand_dollar_sign(t_gc *gc, t_token **tokens,
	t_env *env, char *str)
{
	char	*new_str;
	char	**char_tmp;
	int		i;

	i = 0;
	printf("here1\n");
	new_str = handle_expand(gc, str, env);
	if ((detect_dollar_sign_insquote(str) == 1) || (detect_token_type_indolarsign(new_str) == 1))
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
	printf("HERE\n");
	if ((detect_quotes(ins->export) == 1) || (count_dollarsign_between_egall(ins->str) == 1))
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
	else
	{
		new_str = handle_double_single_quotes(gc, new_str);
		add_element_to_tokens(gc, tokens, new_str);
	}
}

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

void	initia_str_value(t_gc *gc, t_str_inputs **instr,
	char *str, char *export)
{
	(*instr)->export = gc_strdup(gc, export);
	(*instr)->str = gc_strdup(gc, str);
}

void	handle_echo_expand_element(t_gc *gc, t_token **tokens, t_env *env,
	t_str_inputs *str)
{
	if (its_have_dollar_signe(str->str))
		handle_expand_dollar_sign_echo(gc, tokens, env, str->str);
	else
		handle_val_before_addtokens(gc, tokens, str->str);
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
	else if (( (ft_strncmp(new_str, "<", 1) == 0) || (ft_strncmp(new_str, ">", 1) == 0)
	|| (ft_strncmp(new_str, ">>", 2) == 0) || (ft_strncmp(new_str, "<<", 2) == 0)
	|| (ft_strncmp(new_str, "|", 1) == 0)) && instr->echo_str)
	{
		new_token = ft_lstnew(gc, new_str, 1, 1);
		ft_lstadd_back(tokens, new_token);
	}
	else if (tmp->prev && ft_strcmp(tmp->prev->str, "echo") == 0)
	{
		initia_str_value(gc, &instr, tmp->str, tmp->prev->str);
		handle_echo_expand_element(gc, tokens, env, instr);
	}
	else if (its_have_dollar_signe(tmp->str))
		handle_expand_dollar_sign(gc, tokens, env, tmp->str);
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
