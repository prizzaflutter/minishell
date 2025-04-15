/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:10:16 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/14 16:25:52 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_herdoc_input(char *str)
{
	char *line;
	int fd;
	int i;
	
	unlink("heredoc_tmp");
	fd = open("heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	i = 0;
	while (1)
	{
		line = readline("herdoc> ");
		if (!line || ft_strcmp(line, str) == 0)
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	return (fd);
}

int handle_herdocs(t_token *t_token)
{
	int fd;
	while (t_token)
	{
		if (t_token->type == HEREDOC && t_token->next && t_token->next->type == WORD)
		{
			fd = handle_herdoc_input(t_token->next->str);
			if (fd < 0)
				return (-1);
			t_token = t_token->next;
		}
		t_token = t_token->next;
	}
	return (fd);
}
