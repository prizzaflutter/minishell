/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:39:46 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/16 11:28:05 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**configure_splited_key_value(t_gc *gc, char *equel_pos,
		char *str, int is_append)
{
	char	**result;

	result = gc_malloc(gc, sizeof(char *) * 3, 0);
	if (!result)
		return (NULL);
	if (!equel_pos)
	{
		result[0] = gc_strdup(gc, str);
		result[1] = NULL;
	}
	else if (is_append == 1)
	{
		result[0] = gc_strndup(gc, str, equel_pos - str - 1);
		if(*(equel_pos + 1) != '\0')
			result[1] = gc_strdup(gc, equel_pos + 1);
		else
			result[1] = gc_strdup(gc, "");
	}
	else
	{
		result[0] = gc_strndup(gc, str, equel_pos - str);
		if (*(equel_pos + 1) != '\0')
			result[1] = gc_strdup(gc, equel_pos + 1);
		else
			result[1] = gc_strdup(gc, "");
	}
	result[2] = NULL;
	return (result);
}

char	**split_key_value(t_gc *gc, char *str, int *is_append)
{
	char	**result;
	char	*equal_pos;

	*is_append = 0;
	equal_pos = ft_strchr(str, '=');
	if (equal_pos && equal_pos > str )
	{
		if(*(equal_pos - 1) == '+')
			*is_append = 1;
	}
	result = configure_splited_key_value(gc, equal_pos, str, *is_append);
	return (result);
}

int	is_valid_identifier(const char *str)
{
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}
