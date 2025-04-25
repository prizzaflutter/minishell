/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_list_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:48:32 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/25 11:27:44 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_commands(t_gc *gc, t_token *tokens);
char **get_inoutfile(t_gc *gc, t_token *tokens);

t_command	*ft_lstnew_command(t_gc *gc, t_token *tokens)
{
	t_command	*nvcommand;

	nvcommand = (t_command *)gc_malloc(gc, sizeof(t_command), 3);
	if (!nvcommand)
	{
		printf("Error in malloc command");
		return (NULL);
	}
	nvcommand->cmd = get_commands(gc, tokens);
	nvcommand->inoutfile = get_inoutfile(gc, tokens);
	nvcommand->fd_in = -2;
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

int nbr_of_commands(t_token *tokens)
{
	int		i;

	i = 0;
	while (tokens)
	{
		if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT || tokens->type == APPEND)
			tokens = tokens->next;
		else if (tokens->type == WORD)
			i++;
		else if (tokens->type == PIPE)
			return (i);
		tokens = tokens->next;
	}
	return (i);
}

char **get_commands(t_gc *gc, t_token *tokens)
{
	char    **commands;
	int     i;

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
		{
			commands[i] = NULL;
			return (commands);
		}
		else if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT || tokens->type == APPEND)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	commands[i] = NULL;
	return (commands);
}

int nbr_of_inoutfile(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT || tokens->type == APPEND)
		{
			if (tokens->next)
				i+=2;
			else
				i++;
		}
		else if (tokens->type == PIPE)
			return (i);
		tokens = tokens->next;
	}
	return (i);
}

char **get_inoutfile(t_gc *gc, t_token *tokens)
{
	char	**inoutfiles;
	int		i;

	i = 0;
	inoutfiles = gc_malloc(gc, sizeof(char *) * (nbr_of_inoutfile(tokens) + 1), 0);
	if (!inoutfiles)
		return (NULL);
	while (tokens)
	{
		if (tokens->type != WORD && tokens->type != PIPE)
		{
			inoutfiles[i] = gc_strdup(gc, tokens->str);
			i++;
			if (tokens->next)
			{
				inoutfiles[i] = gc_strdup(gc, tokens->next->str);
				i++;
				tokens = tokens->next;
			}
		}
		else if (tokens->type == PIPE)
		{
			
			inoutfiles[i] = NULL;
			return (inoutfiles);
		}
		tokens = tokens->next;
	}
	inoutfiles[i] = NULL;
	return (inoutfiles);
}

void build_command_list(t_gc *gc, t_token *tokens, t_command **cmd_list)
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
		// fd = handle_herdocs(gc, start, env);
		cmd = ft_lstnew_command(gc, start);
		ft_lstadd_back_commmand(cmd_list, cmd);
		if (end)
			start = end->next;
		else
			break;
	}
}
