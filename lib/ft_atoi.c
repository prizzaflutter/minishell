/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:38:48 by iaskour           #+#    #+#             */
/*   Updated: 2025/05/13 13:34:54 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_overflow(int set, char	*new_status)
{
	static char	*is_overflow;

	if (set)
		is_overflow = new_status;
	return (is_overflow);
}

int	ft_atoi(const char *str)
{
	long	num;
	long	holder;
	int		muns;

	holder = 0;
	while (*str != '\0' && ((*str >= 9 && *str <= 13) || (*str == 32)))
		str++;
	muns = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			muns = -1;
		str++;
	}
	num = 0;
	while (ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
		if (num < holder)
			return (is_overflow(1, "overflow"), -(muns + 1)/ 2);
		holder = num;
		str++;
	}
	return (num * muns);
}
