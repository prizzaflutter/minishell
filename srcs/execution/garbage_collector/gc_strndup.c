/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:54:17 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/30 16:08:22 by iaskour          ###   ########.fr       */
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
	if (!des)
		return (NULL);
	ft_memcpy(des, str, len);
	des[len] = '\0';
	return (des);
}
