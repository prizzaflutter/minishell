/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:19:06 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/22 17:17:39 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew(t_gc *gc, char *content)
{
	t_token	*nvtlist;

	nvtlist = (t_token *)gc_malloc(gc, sizeof(t_token), 1);
	if (!nvtlist)
	{
		printf("Error in malloc");
		return (NULL);
	}
	nvtlist->str = content;
	nvtlist->type = define_token_type(content);
	nvtlist->next = NULL;
	return (nvtlist);
}
