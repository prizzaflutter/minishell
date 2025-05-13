/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_list_commands_utilis_1.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:19:47 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/13 18:22:28 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_nbr_herdoc(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->type == HEREDOC && tokens->fd_herdoc != -2)
			i++;
		else if (tokens->type == PIPE)
			break ;
		tokens = tokens->next;
	}
	return (i);
}

void	close_herdoc_fd(t_token **tokens)
{
	int		nbrh;
	int		i;
	t_token	*tmp;

	nbrh = count_nbr_herdoc(*tokens);
	tmp = *tokens;
	i = 0;
	while (tmp && i < nbrh - 1)
	{
		if (tmp->type == HEREDOC && tmp->fd_herdoc != -2)
		{
			close(tmp->fd_herdoc);
			tmp->fd_herdoc = -2;
			i++;
		}
		tmp = tmp->next;
	}
}

int	get_herdoc_fd(t_token *tokens)
{
	int	fd;

	fd = -2;
	while (tokens)
	{
		if (tokens->type == HEREDOC && tokens->fd_herdoc != -2)
		{
			fd = tokens->fd_herdoc;
			break ;
		}
		tokens = tokens->next;
	}
	return (fd);
}
