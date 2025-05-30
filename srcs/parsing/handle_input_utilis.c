/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_utilis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:03:55 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/30 11:34:40 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	its_have_dollar_signe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	count_length_without_quotes(char *str)
{
	int		i;
	int		count;
	int		is_quote;
	char	quote_char;

	i = 0;
	count = 0;
	is_quote = 0;
	quote_char = 0;
	while (str[i])
	{
		if (check_quote(str[i], &is_quote, &quote_char) != 0)
		{
			i++;
			continue ;
		}
		else
			count++;
		i++;
	}
	return (count);
}

char	*handle_double_single_quotes(t_gc *gc, char *str)
{
	char	*new_str;
	int		is_quote;
	char	quote_char;
	int		i;
	int		j;

	i = 0;
	j = 0;
	is_quote = 0;
	quote_char = 0;
	new_str = gc_malloc(gc, sizeof(char)
			* (count_length_without_quotes(str) + 1), 0);
	while (str[i])
	{
		if (check_quote(str[i], &is_quote, &quote_char) != 0)
		{
			i++;
			continue ;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

int	count_dollarsign_between_egall(char *str)
{
	int	cm_dr;
	int	cm_df;
	int	i;

	i = 0;
	cm_df = 0;
	cm_dr = 0;
	while (str[i])
	{
		if (str[i] == '$')
			cm_dr++;
		if (str[i] == '=')
			break ;
		i++;
	}
	while (str[i])
	{
		if (str[i] == '$')
			cm_df++;
		i++;
	}
	if (cm_dr > 0 && cm_df > 0)
		return (1);
	return (0);
}

void	handle_expand_dollar_sign_echo(t_gc *gc, t_token **tokens,
	t_env *env, char *str)
{
	char	*new_str;
	char	**char_tmp;
	int		i;

	i = 0;
	new_str = handle_double_single_quotes(gc, str);
	new_str = handle_expand(gc, new_str, env);
	if (detect_quotes(str) == 1)
		add_element_to_tokens(gc, tokens, new_str);
	else
	{
		char_tmp = ft_split(gc, new_str);
		i = 0;
		while (char_tmp[i])
		{
			add_element_to_tokens(gc, tokens, char_tmp[i]);
			i++;
		}
	}
}
