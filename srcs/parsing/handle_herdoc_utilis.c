/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_herdoc_utilis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:30:44 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/13 21:40:59 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


typedef struct g_gc_env{
	t_gc *gc;
	t_env *env;
}t_gc_env;

int	take_the_herdoc_val(t_gc *gc, char *line, char *str, t_env *env, int fd)
{
	char	*new_str;

	new_str = handle_expand_generale(gc, line, detect_quotes(str, 1), env);
	if (!new_str)
	{
		free(line);
		close(fd);
		return (0);
	}
	write(fd, new_str, ft_strlen(new_str));
	write(fd, "\n", 1);
	free(line);
	return (1);
}

int	all_child_process(t_gc *gc, char *str, t_env *env, int fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("herdoc>");
		if (!line || ft_strcmp(line, handle_delemitre(gc, str)) == 0)
			break ;
		if (!take_the_herdoc_val(gc, line, str, env, fd))
			return (0);
	}
	free(line);
	close(fd);
	return (1);
}

int	handle_child_status( t_token *tokens, int status, int fd, int fd1)
{
	close(fd);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(fd1);
		tokens->fd_herdoc = -2;
		exit_status(1, 128 + WTERMSIG(status));
		return (0);
	}
	tokens->fd_herdoc = fd1;
	exit_status(1, WEXITSTATUS(status));
	return (1);
}

int	handle_herdoc_input(t_gc *gc, char *str, t_token *tokens, t_env *env)
{
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
		if (!all_child_process(gc, str, env, fd))
			exit (1);
		exit (0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (!handle_child_status(tokens, status, fd, fd1))
			return (fd);
		return (fd1);
	}
}
