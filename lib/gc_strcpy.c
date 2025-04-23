/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:37:36 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/22 17:15:45 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gc_strcpy(t_gc *gc, char const *str, char charset)
{
	int		i;
	int		len;
	char	*res;
	char	quote_char;

	i = 0;
	len = 0;
	quote_char = 0;
	while (str[len] != '\0' && (quote_char || str[len] != charset))
    {
        if (!quote_char && (str[len] == '"' || str[len] == '\''))
        {
            quote_char = str[len++];
            while (str[len] != '\0' && str[len] != quote_char)
                len++;
            if (str[len] == quote_char)
                len++;
            quote_char = 0;
        }
        else
            len++;
    }
	res = gc_malloc(gc, len + 1, 0);
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}