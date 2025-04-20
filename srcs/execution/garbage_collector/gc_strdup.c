/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:54:17 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/19 14:54:40 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gc_strdup(t_gc *gc, const char *str)
{
	char	*des;
	size_t	len;

	len = ft_strlen(str) + 1;
	des = (char *)gc_malloc(gc, len);
	if(!des)
		return (NULL);
	ft_memcpy(des, str, len);
	return (des);
}
