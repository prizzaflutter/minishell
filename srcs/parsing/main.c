/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:37:45 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/17 16:56:51 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_list(t_token *tokens)
{
	t_token *current = tokens;
	int i = 1;
	if (!tokens)
	{
		printf("list is empty\n");
		return;
	}
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

int add_tokens_elemnt(char *str, t_token **tokens, t_env *env)
{
	int fd;

	fd = -1;
	if (handle_unclosed_quotes(str))
		return (-1);
	if (add_command_element(str, tokens, env))
	{
		printf("Error in add_command_element\n");
		return (-1);
	}
	if (handle_unexpected_token(*tokens))
		return (-1);
	fd = handle_herdocs(*tokens, env);
	if (fd < 0)
	{
		printf("Error in handle_herdocs\n");
		return (-1);
	}
	return (fd);
}

void f()
{
	system("leaks minishell");
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_env	*env_struct;
	t_token	*tokens;
	char	*input;
	int		fd;
	int		i;

	atexit(f);
	tokens = NULL;
	env_struct = malloc(sizeof(t_env) * env_size(env));
	if (!env_struct)
		return (1);
	fill_env(env_struct, env);
	input = NULL;
	i = 0;
	fd = -1;

	while ((input = readline("\nfoxThrouth0.7:/>")) != NULL)
	{
		if (!input)
			break ;
		if (*input)
		{
			fd = add_tokens_elemnt(input, &tokens, env_struct);
			if (fd < 0)
			{
				free(input);
				free_list(&tokens);
				continue;
			}
		}
		if (strcmp(input, "exit") == 0)
			break ;
		add_history(input);
		print_list(tokens);
		free_list(&tokens);
	}
	free(input);
	free_list(&tokens);
	return (0);
}
