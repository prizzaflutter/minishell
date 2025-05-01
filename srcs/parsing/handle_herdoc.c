/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:10:16 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/01 16:55:08 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_len_delimeter(char *str)
{
	int	i;
	int	len;
	int		is_quote;
	char	quote_char;

	is_quote = 0;
	quote_char = 0;
	i = 0;
	len = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !is_quote)
		{
			is_quote = 1;
			quote_char = str[i];
		}
		else if (str[i] == quote_char && is_quote)
		{
			is_quote = 0;
			quote_char = 0;
		}
		else if (is_quote)
			len++;
		else 
			len++;
		i++;
	}
	return (len);
}

char	*handle_delemitre(t_gc *gc, char *str)
{
	int		i;
	int		j;
	char	*new_str;
	int		is_quote;
	char	quote_char;

	is_quote = 0;
	quote_char = 0;
	if (!str)
		return (NULL);
	i = 0;
	new_str = gc_malloc(gc, sizeof(char) * (count_len_delimeter(str) + 1), 0);
	if (!new_str)
		return (NULL);
	j = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !is_quote)
		{
			is_quote = 1;
			quote_char = str[i];
		}
		else if (str[i] == quote_char && is_quote)
		{
			is_quote = 0;
			quote_char = 0;
		}
		else if (is_quote)
			new_str[j++] = str[i];
		else 
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	handle_herdoc_input(t_gc *gc, char *str, t_token *tokens, t_env *env)
{
	char	*line;
	char	*new_str;
	char	*new_del;
	int		fd;
	int		fd1;

	unlink("/tmp/.heredoc_tmp");
	fd = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	fd1 = open("/tmp/.heredoc_tmp", O_CREAT | O_RDONLY, 0644);
	unlink("/tmp/.heredoc_tmp");
	if (fd < 0 || fd1 < 0)
		return (close(fd), close(fd1), -1);
	while (1)
	{
		new_del = handle_delemitre(gc, str);
		line = readline("herdoc>");
		if (!line || ft_strcmp(line, new_del) == 0)
			break ;
		new_str = handle_expand_generale(gc, line, detect_quotes(str, 1), env);
		if (!new_str)
			return (free(line), close(fd), close(fd1), -1);
		write(fd, new_str, ft_strlen(new_str));
		write(fd, "\n", 1);
		free(line);
	}
	return (close(fd), tokens->fd_herdoc = fd1, fd);
}

int	handle_herdocs(t_gc *gc, t_token *t_token, t_env *env)
{
	int	fd;
	int	is_heredoc;

	fd = -1;
	is_heredoc = 0;
	while (t_token)
	{
		if (t_token->type == HEREDOC && t_token->next
			&& t_token->next->type == WORD)
		{
			is_heredoc = 1;
			fd = handle_herdoc_input(gc, t_token->next->str, t_token, env);
			if (fd < 0)
				return (-1);
			t_token = t_token->next;
		}
		t_token = t_token->next;
	}
	if (is_heredoc == 0)
		return (-2);
	return (fd);
}
