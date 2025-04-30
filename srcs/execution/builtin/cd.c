/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:36:09 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/30 15:53:12 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_cd(char **argv)
{
	if (!argv[1])
	{
		printf("cd: path required\n");
		return (0);
	}
	if (chdir(argv[1]) != 0)
	{
		perror("cd");
		return (0);
	}
	return (0);
}
