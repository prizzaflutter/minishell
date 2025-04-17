/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:48:03 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/17 14:48:14 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lenstring(long n)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		len++;
		return (len);
	}
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		len;
	char	*res;

	nbr = n;
	len = lenstring(nbr);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	if (nbr == 0)
		res[0] = '0';
	res[len] = '\0';
	len--;
	if (nbr < 0)
	{
		res[0] = '-';
		nbr *= -1;
	}
	while (nbr > 0)
	{
		res[len] = (nbr % 10) + 48;
		nbr /= 10;
		len--;
	}
	return (res);
}
