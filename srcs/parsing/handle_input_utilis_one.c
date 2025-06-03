/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_utilis_one.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:49:41 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/01 15:57:48 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		new_token_tmp = ft_lstnew(gc, res[i], 4, 0);
		ft_lstadd_back(tokens_tmp, new_token_tmp);
		i++;
	}
}

void	add_element_to_tokens(t_gc *gc, t_token **tokens, char *str)
{
	t_token	*new_token;

	new_token = ft_lstnew(gc, str, 1, 0);
	ft_lstadd_back(tokens, new_token);
}

void	handle_val_before_addtokens(t_gc *gc, t_token **tokens, char *str)
{
	char	*new_str;

	new_str = handle_double_single_quotes(gc, str);
	add_element_to_tokens(gc, tokens, new_str);
}
