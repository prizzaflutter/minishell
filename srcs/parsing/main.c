/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:37:45 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/09 10:40:44 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char **env) {
	char *input;
	while ((input = readline(">> ")) != NULL)
	{
		if (*input)
			add_history(input);
		free(input);
	}
	return (0);
}