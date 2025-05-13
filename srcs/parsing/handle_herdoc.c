/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:10:16 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/13 19:57:12 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_len_delimeter(char *str)
{
	int		i;
	int		len;
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
	printf("count %d\n",count_len_delimeter(str));
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
	int		fd;
	int		fd1;
	int		status;
	pid_t	pid;

	unlink("/tmp/.heredoc_tmp");
	fd = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	fd1 = open("/tmp/.heredoc_tmp", O_CREAT | O_RDONLY, 0644);
	unlink("/tmp/.heredoc_tmp");
	if (fd < 0 || fd1 < 0)
		return (close(fd), close(fd1), -1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			line = readline("herdoc>");
			if (!line || ft_strcmp(line, handle_delemitre(gc, str)) == 0)
				break ;
			new_str = handle_expand_generale(gc, line, detect_quotes(str, 1), env);
			if (!new_str)
			{
				free(line);
				close(fd);
				exit(1);
			}
			write(fd, new_str, ft_strlen(new_str));
			write(fd, "\n", 1);
			free(line);
		}
		free(line);
		close(fd);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(fd);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			close(fd1);
			tokens->fd_herdoc = -2;
			exit_status(1, 128 + WTERMSIG(status));
			return (fd);
		}
		tokens->fd_herdoc = fd1;
		exit_status(1, WEXITSTATUS(status));
		return (fd1);
	}
}

int	handle_herdocs(t_gc *gc, t_token *t_token, t_env *env)
{
	int	fd;

	fd = -2;
	while (t_token)
	{
		if (t_token->type == HEREDOC && t_token->next
			&& t_token->next->type == WORD)
		{
			fd = handle_herdoc_input(gc, t_token->next->str, t_token, env);
			if (fd < 0)
				return (-1);
			t_token = t_token->next;
		}
		t_token = t_token->next;
	}
	return (fd);
}
