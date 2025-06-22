/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utilis_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:10:50 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/22 15:23:39 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_execute_cmds_list(t_gc *gc, t_token *tokens,
	t_command *cmds, t_env **ens)
{
	build_command_list(gc, tokens, &cmds);
	execute_command(gc, cmds, ens);
	clean_fd_herdoc(tokens);
}

int	initial_main_struct(t_main_var **mvar, char **env)
{
	(*mvar)->tokens = NULL;
	(*mvar)->input = NULL;
	(*mvar)->cmds = NULL;
	(*mvar)->fd = -1;
	(*mvar)->gc = malloc(sizeof(t_gc));
	if (!(*mvar)->gc)
		return (1);
	(*mvar)->gc->head = NULL;
	(*mvar)->ens = fill_env((*mvar)->gc, env);
	return (0);
}

void	fill_env_manual(t_main_var *mv)
{
	char	cwd[1024];
	char	**args;
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)))
		pwd = gc_strjoin(mv->gc, "PWD=", cwd);
	else
		pwd = gc_strdup(mv->gc, "PWD");
	args = gc_malloc(mv->gc, sizeof(char *) * 5, 0);
	args[0] = gc_strdup(mv->gc, "export");
	args[1] = gc_strdup(mv->gc, pwd);
	args[2] = gc_strdup(mv->gc, "OLDPWD");
	args[3] = gc_strdup(mv->gc, "PATH=/run/host/usr/bin:"
			"/run/host/usr/local/bin:"
			"/usr/local/bin:/usr/local/sbin:"
			"/usr/bin:/usr/sbin:/bin:/sbin:.");
	args[4] = NULL;
	my_export(mv->gc, &mv->ens, args, 0);
}

int	max_herdoc_element(t_token *tokens)
{
	int	cm;

	cm = 0;
	while (tokens)
	{
		if (ft_strcmp(tokens->str, "<<") == 0 && tokens->type == HEREDOC)
			cm++;
		tokens = tokens->next;
	}
	if (cm > 16)
		return (1);
	return (0);
}
