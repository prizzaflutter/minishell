/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_utilis1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:49:41 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/28 09:57:45 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	handle_val_before_addtokens(t_gc *gc, t_token **tokens, char *str)
{
	char	*new_str;

	new_str = handle_double_single_quotes(gc, str);
	add_element_to_tokens(gc, tokens, new_str);
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
