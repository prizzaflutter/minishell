/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_utilis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:03:55 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/02 15:04:56 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_expand_dollar_sign_export(t_gc *gc, t_token **tokens,
	t_env *env, t_str_inputs *ins)
{
	char	*new_str;
	char	**char_tmp;
	int		i;

	i = 0;
	new_str = handle_expand(gc, ins->str, env);
	if ((detect_quotes(ins->export) == 1)
		|| (count_dollarsign_between_egall(ins->str) == 1))
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

void	handle_expand_dollar_sign(t_gc *gc, t_token **tokens,
	t_env *env, char *str)
{
	char	*new_str;
	char	**char_tmp;
	int		i;

	i = 0;
	new_str = handle_expand(gc, str, env);
	printf("str => %s\n", new_str);
	if ((detect_dollar_sign_insquote(str) == 1)
		|| (detect_token_type_indolarsign(new_str) == 1) || new_str[i] == '\0')
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

char	*new_value_expand(t_gc *gc, t_env *env, char *str)
{
	char	*new_str;
	int		i;
	char	**sp;

	i = 0;
	sp = ft_split_expand(gc, str);
	while (sp[i])
	{
		sp[i] = handle_double_single_quotes(gc, sp[i]);
		sp[i] = handle_expand(gc, sp[i], env);
		i++;
	}
	i = 0;
	if (sp[i])
		new_str = gc_strdup(gc, sp[i]);
	while (sp[i] && sp[i + 1])
	{
		new_str = ft_strjoin(gc, new_str, sp[i + 1]);
		i++;
	}
	return (new_str);
}

void	handle_expand_dollar_sign_echo(t_gc *gc, t_token **tokens,
	t_env *env, char *str)
{
	char	*new_str;
	char	**char_tmp;
	int		i;

	if (detect_dollar_sign_insquote(str) || detect_quotes(str))
	{
		printf("HERE1\n");
		new_str = new_value_expand(gc, env, str);
		add_element_to_tokens(gc, tokens, new_str);
	}
	else
	{
		printf("HERE2\n");
		new_str = handle_double_single_quotes(gc, str);
		new_str = handle_expand(gc, new_str, env);
		char_tmp = ft_split(gc, new_str);
		i = 0;
		while (char_tmp[i])
		{
			add_element_to_tokens(gc, tokens, char_tmp[i]);
			i++;
		}
	}
}

void	handle_echo_expand_element(t_gc *gc, t_token **tokens, t_env *env,
	char *str)
{
	if (its_have_dollar_signe(str))
		handle_expand_dollar_sign_echo(gc, tokens, env, str);
	else
		handle_val_before_addtokens(gc, tokens, str);
}
