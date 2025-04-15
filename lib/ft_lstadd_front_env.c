/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:03:17 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/15 10:28:59 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_front_env(t_env **env, t_env *new_env)
{
	if (!env || new_env == NULL)
		return ;
	new_env -> next = *env;
	*env = new_env;
}
