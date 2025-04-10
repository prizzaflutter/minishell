/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:37:45 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/10 11:51:56 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main() {
	char *input;
	char *new_inp;
	while ((input = readline(">>")) != NULL)
	{
		if (*input)
		{
			new_inp = add_space_inputs(input);
			rl_on_new_line();
            rl_replace_line(new_inp, 0);
            rl_redisplay();   
			add_history(input);
		}
		free(input);
	}
	return (0);
}