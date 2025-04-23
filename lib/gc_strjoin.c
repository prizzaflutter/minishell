/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:56:46 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/22 17:15:51 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gc_strjoin(t_gc *gc, char const *s1, char const *s2)
{
	char	*str;
	size_t	lenght;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lenght = (ft_strlen(s1) + ft_strlen(s2));
	str = (char *)gc_malloc(gc, (lenght + 1) * sizeof(char), 0);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1 != NULL && i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 != NULL && i < lenght)
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
