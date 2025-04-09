/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:12:44 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/09 10:08:42 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

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
