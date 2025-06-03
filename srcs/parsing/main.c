/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:06:47 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/03 17:48:09 by aykassim         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	t_main_var	*mv;
	int			check;

	(void)ac;
	(void)av;
	mv = malloc(sizeof(t_main_var));
	if (!mv || initial_main_struct(&mv, env) == 1)
		return (1);
	call_main_signals();
	rl_catch_signals = 0;
	while (1)
	{
		mv->input = readline("minishell:</>");
		check = the_main_work(mv);
		if (check == 2)
			break ;
		if (check == 3 || check == 4)
			continue ;
		if (mv->tokens)
			build_execute_cmds_list(mv->gc, mv->tokens, mv->cmds, &mv->ens);
		free_element_inside_while(&mv);
	}
	free_element_in_end(&mv);
	return (exit_status(1, exit_status(0, 0)));
}
