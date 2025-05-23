/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utilis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:37:23 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/23 10:14:22 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_tokens_elemnt(t_gc *gc, char *str, t_token **tokens, t_env *env)
{
	int	fd;

	fd = -2;
	if (handle_unclosed_quotes(str))
		return (exit_status(1, 2), -1);
	if (add_command_element(gc, str, tokens, env))
		return (-1);
	if (handle_unexpected_token(*tokens))
		return (exit_status(1, 2), -1);
	fd = handle_herdocs(gc, *tokens, env);
	if (fd == -1)
		return (-1);
	return (fd);
}

void	clean_fd_herdoc(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == HEREDOC && tokens->fd_herdoc != -2)
		{
			close(tokens->fd_herdoc);
			tokens->fd_herdoc = -2;
		}
		tokens = tokens->next;
	}
}

int	the_main_work(t_main_var	*mv)
{
	if (!mv->input)
		return (2);
	if (ft_is_only_whitespace(mv->input))
	{
		free(mv->input);
		return (3);
	}
	if (*mv->input)
		add_history(mv->input);
	mv->fd = add_tokens_elemnt(mv->gc, mv->input, &mv->tokens, mv->ens);
	if (mv->fd == -1)
	{
		gc_clear(mv->gc, 1);
		mv->tokens = NULL;
		free(mv->input);
		return (4);
	}
	return (0);
}

void	free_element_inside_while(t_main_var **mv)
{
	clean_fd_herdoc((*mv)->tokens);
	gc_clear((*mv)->gc, 1);
	gc_clear((*mv)->gc, 3);
	(*mv)->tokens = NULL;
	(*mv)->cmds = NULL;
	free((*mv)->input);
}

void	free_element_in_end(t_main_var **mv)
{
	clean_fd_herdoc((*mv)->tokens);
	gc_clear((*mv)->gc, 1);
	gc_clear((*mv)->gc, 0);
	free((*mv)->gc);
	free(*mv);
}
