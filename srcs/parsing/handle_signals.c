/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:44:55 by aykassim          #+#    #+#             */
/*   Updated: 2025/06/18 15:46:50 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		exit_status(1, 130, "handle ctrl c");
	}
}

void	call_main_signals(void)
{
	if (signal(SIGINT, handle_ctrl_c) == SIG_ERR)
		perror("signal failed");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal failed");
}

void	call_herdoc_signals(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		perror("signal failed");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal failed");
}

void	child_default_signal(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		perror("signal failed");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		perror("signal failed");
}
