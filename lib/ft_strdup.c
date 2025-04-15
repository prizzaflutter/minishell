/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:44:42 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/15 10:50:51 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*des;
	size_t	len;

	len = ft_strlen(s1);
	des = (char *)malloc(len + 1);
	if (!des)
		return (NULL);
	ft_memcpy(des, s1, len + 1);
	return (des);
}
