/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_list_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:48:32 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/21 11:00:40 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_lstnew_command(t_gc *gc, t_token *tokens)
{
	t_command	*nvcommand;

	nvcommand = (t_command *)gc_malloc(gc, sizeof(t_command), 3);
	if (!nvcommand)
		return (NULL);
	nvcommand->cmd = get_commands(gc, tokens);
	nvcommand->inoutfile = get_inoutfile(gc, tokens);
	close_herdoc_fd(&tokens);
	nvcommand->fd_in = get_herdoc_fd(tokens);
	nvcommand->next = NULL;
	nvcommand->prev = NULL;
	return (nvcommand);
}

t_command	*ft_lstlast_command(t_command *lst)
{
	t_command	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current -> next != NULL)
		current = current -> next;
	return (current);
}

void	ft_lstadd_back_commmand(t_command **lst, t_command *new)
{
	t_command	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = ft_lstlast_command(*lst);
		last->next = new;
		new->prev = last;
	}
}

void	build_command_list(t_gc *gc, t_token *tokens, t_command **cmd_list)
{
	t_token		*start;
	t_token		*end;
	t_command	*cmd;

	start = tokens;
	while (start)
	{
		end = start;
		while (end && end->type != PIPE)
			end = end->next;
		cmd = ft_lstnew_command(gc, start);
		ft_lstadd_back_commmand(cmd_list, cmd);
		if (end)
			start = end->next;
		else
			break ;
	}
}
