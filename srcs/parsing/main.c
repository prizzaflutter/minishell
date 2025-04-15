/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:37:45 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/15 11:42:51 by aykassim         ###   ########.fr       */
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

int free_list(t_token **tokens)
{
	t_token *tmp;
	if (!tokens || !*tokens)
		return (0);
	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->str);
		free(tmp);
	}
	*tokens = NULL;
	return (0);
}
// int main()
// {
// 	t_token *tokens = NULL;
// 	add_command_element("echo >> test << \"hello world\" > file.txt | test|hello word | aaa<< aa>> abcd > aaaaaa", &tokens);
// 	print_list(tokens);
// 	return 0;
// }

// int main()
// {
// 	t_token *token;
// 	token = ft_lstnew("aaa$HOME");
// 	char *res = expand_variable(token);
// 	if (res)
// 	{
// 		printf("Expanded variable: %s\n", res);
// 	}
// 	else
// 	{
// 		printf("Variable not found\n");
// 	}
// }


int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	int length = env_size(env);
	printf("the length of env is : %d\n", length);
	t_env *env_struct = malloc(sizeof(t_env) * length);
	fill_env(env_struct, env);
	t_env *current = env_struct;
	while (current)
	{
		printf("Key : %s\n", current->key);
		printf("Value : %s\n", current->value);
		current = current->next;
	}
	char *str = "aaaaa ''$USER'' aaaaa";

	printf("the value is .%s.\n", handle_expand(str));
}

// int main() {
// 	char *input;
// 	int fd;
// 	t_token *tokens = NULL;
// 	while ((input = readline("\nfoxThrouth0.7$")) != NULL)
// 	{
// 		if (*input)
// 		{
// 			add_command_element(input, &tokens); 
// 			if (handle_unexpected_token(tokens))
// 			{
// 				free(input);
// 				free_list(&tokens);
// 				continue;
// 			}
// 			if (handle_herdocs(tokens))
// 			{
// 				fd = handle_herdocs(tokens);
// 				if (fd < 0)
// 				{
// 					free(input);
// 					free_list(&tokens);
// 					continue;
// 				}
// 				printf("fd = %d\n", fd);
// 			}
// 			add_history(input);
// 		}
// 		free(input);
// 		print_list(tokens);
// 		free_list(&tokens);
// 	}
// 	return (0);
// }