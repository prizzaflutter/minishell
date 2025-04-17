/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:10:16 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/17 13:31:55 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_delemitre(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	if (!str)
		return (NULL);
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			len++;
		i++;
	}
	new_str = malloc(sizeof(char) * (len + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int handle_herdoc_input(char *str, t_env *env)
{
	char *line;
	int fd;
	int i;
	char *new_str;
	char *new_del;
	
	unlink("heredoc_tmp");
	fd = open("heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	i = 0;
	while (1)
	{
		new_del = handle_delemitre(str);
		line = readline("herdoc> ");
		if (!line || ft_strcmp(line, new_del) == 0)
			break;
		new_str = handle_expand_herdoc(line, detect_quotes(str, 1), env);
		if (!new_str)
		{
			free(line);
			close(fd);
			unlink("heredoc_tmp");
			return (-1);
		}
		write(fd, new_str, ft_strlen(new_str));
		write(fd, "\n", 1);
		free(line);
		free(new_str);
	}
	// unlink("heredoc_tmp");
	return (fd);
}

int handle_herdocs(t_token *t_token, t_env *env)
{
	int fd;
	while (t_token)
	{
		if (t_token->type == HEREDOC && t_token->next && t_token->next->type == WORD)
		{
			fd = handle_herdoc_input(t_token->next->str, env);
			if (fd < 0)
				return (-1);
			t_token = t_token->next;
		}
		t_token = t_token->next;
	}
	return (fd);
}
