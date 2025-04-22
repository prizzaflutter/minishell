/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:06:10 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/21 08:57:42 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status(int set, int new_status)
{
	static int status;

	if (set)
		status  = new_status;
	printf("the exit status opened : %d\n", status);
	return (status);
}
