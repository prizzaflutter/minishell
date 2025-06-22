/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:03:54 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/21 20:12:06 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	just_checks(t_main_var	*mv, char **env)
{
	if (!mv || initial_main_struct(&mv, env) == 1)
		return (0);
	if (!isatty (0))
		return (free(mv), 0);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_main_var	*mv;
	int			check;

	(void)ac;
	(void)av;
	mv = malloc(sizeof(t_main_var));
	if (!just_checks(mv, env))
		return (1);
	if (!mv->ens)
		fill_env_manual(mv);
	call_main_signals();
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
