/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:37:59 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/21 10:07:19 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	excute_single_command(t_gc *gc, t_command *cmd, t_env **env)
{
	char	**cmd_args;
	char	*cmd_path;
	char	**env_array;

	cmd_args = cmd->cmd;
	cmd_path = configure_path(gc, *cmd->cmd, *env);
	env_array = convert_env_to_array(gc, *env);
	if (execve(cmd_path, cmd_args, env_array) == -1)
	{
		if (errno == EACCES)
			return (ft_printf("minishell: Permission denied\n"),
				exit(126), 0);
		else if (errno == ENOENT)
			return (ft_printf("minishell: No such file or directory\n"),
				exit(127), 0);
		else if (errno == ENOTDIR)
			return (ft_printf("minishell: Not a directory\n"), exit(126), 0);
	}
	return (1);
}

void	my_parent_process(pid_t pid, int *status)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		perror("signal failed");
	waitpid(pid, status, 0);
	call_main_signals();
	if (WIFEXITED(*status))
		exit_status(1, WEXITSTATUS(*status));
	else if (WIFSIGNALED(*status))
		exit_status(1, 128 + WTERMSIG(*status));
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGQUIT)
		ft_printf("Quit: 3\n");
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
		ft_printf("\n");
}

void	handle_redirection_and_execute(char *build_in_f,
	t_gc *gc, t_command *cmd, t_env *env)
{
	int		out_file;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < -1)
		return (ft_printf("for error\n"), exit(1));
	if (pid == 0)
	{
		child_default_signal();
		out_file = handle_redirections_single(cmd);
		if (out_file == -1)
			exit(1);
		if (is_on_child(build_in_f, cmd, env, gc) == 0)
			excute_single_command(gc, cmd, &env);
		exit(0);
	}
	else
		my_parent_process(pid, &status);
}

void	handle_single_command(t_gc *gc, t_command *cmd, t_env **env)
{
	char	*build_in_f;
	int		org_stdin ;
	int		org_stdout;

	save_int_out(&org_stdin, &org_stdout);
	if ((cmd->cmd[0] == NULL && cmd->inoutfile[0] == NULL))
	{
		ft_printf("am over her\n");
		return ;
	}
	build_in_f = is_builtin(*cmd->cmd);
	if (is_on_parent(build_in_f, cmd, env, gc) == 0)
		handle_redirection_and_execute(build_in_f, gc, cmd, *env);
	restore_in_out(&org_stdin, &org_stdout);
}
