/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:04:07 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/13 11:35:23 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	excute_single_command(t_gc *gc, t_command *cmd, t_env **env)
{
	char	**cmd_args;
	char	*cmd_path;
	char	**env_array;

	cmd_args = cmd->cmd;
	if (!cmd_args)
		return (0);
	cmd_path = configure_path(gc, *cmd->cmd, *env);
	if (!cmd_path)
		return (0);
	env_array = convert_env_to_array(gc, *env);
	if (!env_array)
		return (0);
	if (execve(cmd_path, cmd_args, env_array) == -1)
		return (printf("Error: EXECVE => (first child)"),
			exit_status(1, 127), 0);
	return (1);
}

void	handle_redirection_and_execute(char *build_in_f,
	t_gc *gc, t_command *cmd, t_env *env)
{
	int		out_file;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		out_file = handle_redirections_single(cmd);
		if (out_file == -1)
			exit(1);
		if (is_on_child(build_in_f, cmd, env, gc) == 0)
			
		{
			if (excute_single_command(gc, cmd, &env) == 0)
				return (perror("Excve Error :"), exit_status(1, 127), exit(1));
		}
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			exit_status(1, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			exit_status(1, 128 + WTERMSIG(status));
	}
}

void	handle_single_command(t_gc *gc, t_command *cmd, t_env *env)
{
	char	*build_in_f;
	int		org_stdin ;
	int		org_stdout;

	save_int_out(&org_stdin, &org_stdout);
	if ((cmd->cmd[0] == NULL && cmd->inoutfile[0] == NULL))
		return ;
	build_in_f = is_builtin(*cmd->cmd);
	if (is_on_parent(build_in_f, cmd, env, gc) == 0)
		handle_redirection_and_execute(build_in_f, gc, cmd, env);
	restore_in_out(&org_stdin, &org_stdout);
}
