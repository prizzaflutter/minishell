/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:06:10 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/11 12:25:56 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status(int set, int new_status)
{
	static int	status;

	if (set)
		status = new_status;
	return (status);
}
