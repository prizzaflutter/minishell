/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_utilis_two.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:46:33 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/01 15:53:38 by aykassim         ###   ########.fr       */
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
		else if (((ft_strncmp(&str[i], "<", 1) == 0)
				|| (ft_strncmp(&str[i], ">", 1) == 0)
				|| (ft_strncmp(&str[i], ">>", 2) == 0)
				|| (ft_strncmp(&str[i], "<<", 2) == 0))
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
		if ((ft_strncmp(&str[i], "<", 1) == 0)
			|| (ft_strncmp(&str[i], ">", 1) == 0)
			|| (ft_strncmp(&str[i], ">>", 2) == 0)
			|| (ft_strncmp(&str[i], "<<", 2) == 0))
			return (1);
		else
			i++;
	}
	return (0);
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
