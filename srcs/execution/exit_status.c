/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:06:10 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/22 13:05:59 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status(int set, int new_status)
{
    // set ==== > set = 1 : new_status : value
    // get ===== >  set = 0 : new _status : 0
	static int status;

	if (set)
		status = new_status;
	// printf("the exit status opened : %d\n", status);
	return (status);
}
