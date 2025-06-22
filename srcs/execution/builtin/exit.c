/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:53:05 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/21 17:56:46 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_num(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '+' || str[i] == '-') && str[i + 1])
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	exit_checker(int num_args, char **args, int is_pipe)
{
	int	num;

	if (!is_valid_num(args[1]))
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	if (num_args > 1)
	{
		ft_printf("minishell: exit: too many arguments\n");
		if (is_pipe)
			exit (1);
		else
		{
			exit_status(1, 1);
			return (1);
		}
	}
	num = ft_atoi(args[1]);
	if (!ft_strcmp(is_overflow(0, " "), "overflow"))
	{
		ft_printf("minishell: exit: %d: numeric argument required\n", num);
		exit(2);
	}
	exit(num);
}

void	my_exit(char **args, int is_pip)
{
	int	status;
	int	num_args;

	if (!is_pip)
		ft_printf("exit\n");
	num_args = count_args(args);
	num_args--;
	if (num_args == 0)
	{
		status = exit_status(0, 0);
		exit(status);
	}
	else
		if (exit_checker(num_args, args, is_pip) == 1)
			return ;
}
