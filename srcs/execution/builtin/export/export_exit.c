/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:48:44 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/21 20:35:42 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_exit(int has_error, int is_pipe)
{
	if (!is_pipe)
	{
		if (has_error)
			exit_status(1, 1);
		else
			exit_status(1, 0);
	}
	else
	{
		if (has_error)
			exit(1);
		else
			exit(0);
	}
}
