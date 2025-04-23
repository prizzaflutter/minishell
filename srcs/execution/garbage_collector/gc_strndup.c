/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:54:17 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/22 17:16:39 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gc_strndup(t_gc *gc, const char *str, size_t n)
{
	char	*des;
	size_t	len;

	len = 0;
	while (str[len] && len < n)
		len++;
	des = (char *)gc_malloc(gc, len + 1, 0);
	if(!des)
		return (NULL);
	ft_memcpy(des, str, len);
	des[len] = '\0';
	return (des);
}
