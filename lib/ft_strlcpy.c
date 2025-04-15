/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:48:36 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/15 10:48:42 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	lens;
	size_t	cpsize;

	lens = ft_strlen(src);
	if (dstsize == 0)
		return (lens);
	if (dstsize - 1 < lens)
		cpsize = dstsize - 1;
	else
		cpsize = lens;
	ft_memcpy(dst, src, cpsize);
	dst[cpsize] = '\0';
	return (lens);
}
