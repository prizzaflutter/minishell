/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:18:21 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/11 10:27:19 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_format(int fd, char format, va_list ap)
{
	if (format == 's')
		ft_putstr_fd(va_arg(ap, void *), fd);
}

void	ft_printf(int fd, const char *format, ...)
{
	va_list		ap;

	if (write(fd, "", 0) == -1)
		return ;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1) != '\0')
			print_format(fd, *(++format), ap);
		else
			ft_putchar_fd(*format, fd);
		format++;
	}
	va_end (ap);
}
