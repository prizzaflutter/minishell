/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:12:01 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/16 11:29:02 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_path(t_env *env, t_gc *gc, char *path)
{
	int		check;
	char	*append;
	t_env	*curr;

	check = 0;
	append = NULL;
	curr = env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, "PWD"))
		{
			if (check == 0)
			{
				path = gc_strjoin(gc, "/", path);
				check = 1;
			}
			append = gc_strjoin(gc, curr->value, path);
			break ;
		}
		curr = curr->next;
	}
	return (append);
}

void	configure_path_splited(t_gc *gc, t_stack **stack, char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (!ft_strcmp(path[i], ".."))
			go_up(stack);
		else if (ft_strcmp(path[i], ".") != 0 || ft_strcmp(path[i], "") != 0)
			add_to_path(gc, path[i], stack);
		i++;
	}
}

char	*convert_to_array(t_gc *gc, t_stack *stack)
{
	t_stack	*current;
	char	*my_string;

	current = stack;
	my_string = gc_strdup(gc, "");
	while (current)
	{
		if (!ft_strcmp(current->path, "..") != 0
			|| ft_strcmp(current->path, ".") != 0
			|| ft_strcmp(current->path, "") != 0)
		{
			my_string = gc_strjoin(gc, my_string, "/");
			my_string = gc_strjoin(gc, my_string, current->path);
		}
		current = current->next;
	}
	return (my_string);
}

char	*normalize_path(t_env *env, t_gc *gc, char *path, int flag)
{
	char	*appended;
	char	**path_splited;
	t_stack	*stack;
	char	*converted;

	stack = NULL;
	appended = append_path(env, gc, path);
	path_splited = gc_split(gc, appended, '/');
	configure_path_splited(gc, &stack, path_splited);
	converted = convert_to_array(gc, stack);
	if (!flag)
		return (appended);
	return (converted);
}
