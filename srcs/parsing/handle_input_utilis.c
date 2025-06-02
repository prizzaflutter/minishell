/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_utilis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:03:55 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/02 19:51:26 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handle_expand_dollar_sign_export(t_gc *gc, t_token **tokens,
// 	t_env *env, t_str_inputs *ins)
// {
// 	char	*new_str;
// 	char	**char_tmp;
// 	int		i;

// 	i = 0;
// 	new_str = handle_expand(gc, ins->str, env);
// 	if ((detect_quotes(ins->export) == 1)
// 		|| (count_dollarsign_between_egall(ins->str) == 1))
// 	{
// 		new_str = handle_double_single_quotes(gc, new_str);
// 		char_tmp = ft_split(gc, new_str);
// 		i = 0;
// 		while (char_tmp[i])
// 		{
// 			add_element_to_tokens(gc, tokens, char_tmp[i]);
// 			i++;
// 		}
// 	}
// 	else
// 	{
// 		new_str = handle_double_single_quotes(gc, new_str);
// 		add_element_to_tokens(gc, tokens, new_str);
// 	}
// }

static size_t	count_word_test(const char *s, char c)
{
	size_t	counter;
	int		in_word;
	int		i;

	i = 0;
	counter = 0;
	in_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && in_word == 0)
		{
			in_word = 1;
			counter++;
		}
		else if (s[i] == c && in_word == 1)
		{
			in_word = 0;
		}
		i++;
	}
	return (counter);
}

int	detect_separator_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
		{
			i++;
			if (str[i] == '=')
				return (1);		
		}
		if (str[i] == '=')
			return (2);
		i++;
	}
	return (0);
}

void	handle_expand_dollar_sign_export(t_gc *gc, t_token **tokens,
	t_env *env, t_str_inputs *ins)
{
	char	*new_str;
	char	**char_tmp;
	int		i;
	char	**new_sp;
	char		**sp;
	
	new_str = gc_strdup(gc, ins->str);
	if (detect_separator_expand(ins->str) == 2)
		sp = gc_split(gc, ins->str, '=');
	else if (detect_separator_expand(ins->str) == 1)
	{
		sp = gc_split(gc, ins->str, '=');
		sp[0] = ft_substr(gc, sp[0], 0, ft_strlen(sp[0]) - 1);
	}
	i = 0;
	if (sp[0] && its_have_dollar_signe(sp[0]) && !detect_dollar_sign_insquote(sp[0]))
	{
		sp[0] = handle_expand(gc, sp[0], env);
		new_sp = gc_split(gc, sp[0], ' ');
		sp[0] = gc_strdup(gc, new_sp[count_word_test(sp[0], ' ') - 1]);
	}
	
	if (detect_separator_expand(ins->str) == 2)
	{
		sp[0] = gc_strjoin(gc, sp[0], "=");
		new_str = gc_strjoin(gc, sp[0], sp[1]);
	}
	else if (detect_separator_expand(ins->str) == 1)
	{
		sp[0] = gc_strjoin(gc, sp[0], "+");
		sp[0] = gc_strjoin(gc, sp[0], "=");
		new_str = gc_strjoin(gc, sp[0], sp[1]);
	}
	new_str = handle_expand(gc, new_str, env);
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
