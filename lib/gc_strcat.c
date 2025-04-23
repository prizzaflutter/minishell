/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:44:46 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/22 17:15:41 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char*	gc_strcat(t_gc *gc, char *dst, const char *src)
{
	char	*result;
	int	j;
	int	i;

	result = (char *)gc_malloc(gc, ft_strlen(dst) + ft_strlen(src) + 1, 0);
	j = 0;
	i = 0;
	while(dst && dst[i])
	{
		result[i] = dst[i];
		i++;
	}
	while(src && src[j])
	{
		result[i + j] = src[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}
