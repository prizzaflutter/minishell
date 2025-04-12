/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:37:45 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/12 15:28:41 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_list(t_token *tokens)
{
	t_token *current = tokens;
	int i = 1;
	while (current != NULL)
	{
		printf("token[%d] = %s\n", i, current->str);
		printf("type[%d] = %d\n", i, current->type);
		current = current->next;
		i++;
	}
}

// int main()
// {
// 	t_token *tokens = NULL;
// 	add_command_element("echo >> test << \"hello world\" > file.txt | test|hello word | aaa<< aa>> abcd > aaaaaa", &tokens);
// 	print_list(tokens);
// 	return 0;
// }

int main() {
	char *input;
	char *new_inp;
	while ((input = readline("\n>>")) != NULL)
	{
		if (*input)
		{
			new_inp = add_space_inputs(input);
			rl_on_new_line();
            rl_replace_line(new_inp, 0);
            rl_redisplay();   
			add_history(input);
			printf("input = %s\n", input);
		}
		free(input);
	}
	return (0);
}