/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:07:33 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/09 11:00:12 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew(char *content)
{
	t_token	*nvtlist;

	nvtlist = (t_token *) malloc(sizeof(t_token));
	if (!nvtlist)
		return (NULL);
	nvtlist->str = content;
	nvtlist->type = 0;
	nvtlist->next = NULL;
	return (nvtlist);
}
