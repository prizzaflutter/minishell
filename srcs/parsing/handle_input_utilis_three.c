/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_utilis_three.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:52:14 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/01 15:53:47 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	detect_dollar_sign_insquote(char *str)
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
		else if (str[i] == '$' && is_quote == 1)
			return (1);
		else
			i++;
	}
	return (0);
}

int	detect_quotes(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

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

void	initia_str_value(t_gc *gc, t_str_inputs **instr,
	char *str, char *export)
{
	(*instr)->export = gc_strdup(gc, export);
	(*instr)->str = gc_strdup(gc, str);
}
