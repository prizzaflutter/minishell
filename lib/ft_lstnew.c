/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:19:06 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/12 16:38:01 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew(char *content)
{
	t_token	*nvtlist;

	nvtlist = (t_token *) malloc(sizeof(t_token));
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
