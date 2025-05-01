/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_list_commands_utilis.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:55:34 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/01 15:44:19 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_of_commands(t_token *tokens)
{
	int		i;

	i = 0;
	while (tokens)
	{
		if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == APPEND)
			tokens = tokens->next;
		else if (tokens->type == WORD)
			i++;
		else if (tokens->type == PIPE)
			return (i);
		tokens = tokens->next;
	}
	return (i);
}

char	**get_commands(t_gc *gc, t_token *tokens)
{
	char	**commands;
	int		i;

	i = 0;
	commands = gc_malloc(gc, sizeof(char *) * (nbr_of_commands(tokens) + 1), 0);
	if (!commands)
		return (NULL);
	while (tokens)
	{
		if (tokens->type == WORD)
		{
			commands[i] = gc_strdup(gc, tokens->str);
			i++;
		}
		else if (tokens->type == PIPE)
			return (commands[i] = NULL, commands);
		else if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == APPEND)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	commands[i] = NULL;
	return (commands);
}

int	nbr_of_inoutfile(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == APPEND || tokens->type == HEREDOC)
		{
			if (tokens->next)
				i += 2;
			else
				i++;
		}
		else if (tokens->type == PIPE)
			return (i);
		tokens = tokens->next;
	}
	return (i);
}

char	**get_inoutfile(t_gc *gc, t_token *tokens)
{
	char	**inoutfiles;
	int		i;

	i = 0;
	inoutfiles = gc_malloc(gc, sizeof(char *)
			* (nbr_of_inoutfile(tokens) + 1), 0);
	if (!inoutfiles)
		return (NULL);
	while (tokens)
	{
		if (tokens->type != WORD && tokens->type != PIPE)
		{
			inoutfiles[i++] = gc_strdup(gc, tokens->str);
			if (tokens->next)
			{
				inoutfiles[i++] = gc_strdup(gc, tokens->next->str);
				tokens = tokens->next;
			}
		}
		else if (tokens->type == PIPE)
			return (inoutfiles[i] = NULL, inoutfiles);
		tokens = tokens->next;
	}
	inoutfiles[i] = NULL;
	return (inoutfiles);
}

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

void close_herdoc_fd(t_token **tokens)
{
	int	nbrh;
	t_token *tmp;
	int	i;

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
