/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:37:45 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/22 19:58:31 by aykassim         ###   ########.fr       */
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
        if (tmp->str)
        {
            free(tmp->str);
            tmp->str = NULL;
        }
        free(tmp);
    }
    *tokens = NULL;
    return (0);
}

int add_tokens_elemnt(t_gc *gc,char *str, t_token **tokens, t_env *env)
{
	int fd;

	fd = -1;
	if (handle_unclosed_quotes(str))
		return (-1);
	if (add_command_element(gc, str, tokens, env))
	{
		printf("Error in add_command_element\n");
		return (-1);
	}
	if (handle_unexpected_token(*tokens))
    {
        exit_status(1, 2);
		return (-1);
    }
	fd = handle_herdocs(gc, *tokens, env);
	if (fd < 0)
	{
		printf("Error in handle_herdocs\n");
		return (-1);
	}
	return (fd);
}

int	ft_isspace(char c)
{
	if  (c == ' ' || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

int	ft_is_only_whitespace(char *str)
{
	int	i = 0;

	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}



int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
    t_gc *gc = malloc(sizeof(t_gc));
    if (!gc)
        return (1);
    gc->head = NULL;
	t_env	*env_struct;
	t_token	*tokens;
	char	*input;
	int		fd;

	tokens = NULL;
    env_struct = fill_env(gc, env);
	input = NULL;
	fd = -1;
	while (1)
    {
        input = readline("\nfoxThrouth0.7:/>");
        if (!input)
            break;
        if (ft_is_only_whitespace(input))
        {
            free(input);
            continue;
        }
        if (*input)
            add_history(input);

        if (ft_strcmp(input, "exit") == 0)
        {
            printf("Exiting...\n");
            free(input);
            break;
        }
        fd = add_tokens_elemnt(gc, input, &tokens, env_struct);
        if (fd < 0)
        {
            gc_clear(gc, 1);
            tokens = NULL;
            free(input);
            continue;
        }
        print_list(tokens);
        gc_clear(gc, 1);
        tokens = NULL;
        free(input);
    }
    gc_clear(gc, 1);
    gc_clear(gc, 0);
    free(gc);
	return (0);
}
