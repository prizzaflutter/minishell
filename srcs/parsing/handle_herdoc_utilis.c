/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc_utilis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:44:30 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/22 15:21:43 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	all_child_process(t_gc *gc, char *str, t_env *env, t_herdoc_h her_fd)
{
	char	*line;
	char	*new_str;

	while (1)
	{
		line = readline("herdoc>");
		if (!line || ft_strcmp(line, handle_delemitre(gc, str)) == 0)
		{
			close(her_fd.fd);
			free(line);
			return (0);
		}
		new_str = handle_expand_herdoc(gc, line, detect_quotes(str), env);
		if (!new_str)
		{
			close(her_fd.fd);
			free(line);
			return (0);
		}
		write(her_fd.fd, new_str, ft_strlen(new_str));
		write(her_fd.fd, "\n", 1);
		free(line);
	}
	close(her_fd.fd);
	return (free(line), 1);
}

int	handle_child_status(t_token *tokens, int status, int fd, int fd1)
{
	close(fd);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(fd1);
		write(1, "\n", 1);
		tokens->fd_herdoc = -2;
		exit_status(1, 130);
		return (0);
	}
	tokens->fd_herdoc = fd1;
	return (1);
}

void	initial_fd_herdoc(int *fd,	int *fd1)
{
	*fd = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	*fd1 = open("/tmp/.heredoc_tmp", O_CREAT | O_RDONLY, 0644);
}

int	handle_herdoc_input(t_gc *gc, char *str, t_token *tokens, t_env *env)
{
	t_herdoc_h	herdoc;
 
	unlink("/tmp/.heredoc_tmp");
	initial_fd_herdoc(&herdoc.fd, &herdoc.fd1);
	unlink("/tmp/.heredoc_tmp");
	if (herdoc.fd < 0 || herdoc.fd1 < 0)
		return (close(herdoc.fd), close(herdoc.fd1), -1);
	herdoc.pid = fork();
	if (herdoc.pid == 0)
	{
		call_herdoc_signals();
		if (!all_child_process(gc, str, env, herdoc))
			exit (1);
		exit (0);
	}
	else
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR)
			perror("signal failed");
		waitpid(herdoc.pid, &herdoc.status, 0);
		call_main_signals();
		if (!handle_child_status(tokens, herdoc.status, herdoc.fd, herdoc.fd1))
			return (-1);
		return (herdoc.fd1);
	}
}
