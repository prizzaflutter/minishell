/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_list_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:56:35 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/19 16:04:26 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	define_token_type(char *str, int quote)
{
	if (quote == 0)
	{
		if (ft_strcmp(str, "|") == 0)
			return (PIPE);
		else if (ft_strcmp(str, "<") == 0)
			return (REDIR_IN);
		else if (strcmp(str, ">") == 0)
			return (REDIR_OUT);
		else if (ft_strcmp(str, "<<") == 0)
			return (HEREDOC);
		else if (ft_strcmp(str, ">>") == 0)
			return (APPEND);
		else
			return (WORD);
	}
	else
		return (WORD);
}

t_token	*ft_lstnew(t_gc *gc, char *content, int flag, int quote)
{
	t_token	*nvtlist;

	nvtlist = (t_token *)gc_malloc(gc, sizeof(t_token), flag);
	if (!nvtlist)
		return (NULL);
	nvtlist->str = content;
	nvtlist->type = define_token_type(content, quote);
	nvtlist->next = NULL;
	nvtlist->prev = NULL;
	nvtlist->fd_herdoc = -2;
	return (nvtlist);
}

t_token	*ft_lstlast(t_token *lst)
{
	t_token	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
}
