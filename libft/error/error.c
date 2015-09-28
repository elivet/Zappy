/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/06 14:46:33 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/14 17:25:10 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include "libft.h"

int		error(const char *msg, ...)
{
	va_list		ap;

	va_start(ap, msg);
	while (*msg)
	{
		if (*msg == '%')
		{
			msg++;
			if (*msg == '%')
				ft_putchar_fd('%', 2);
			else if (*msg == 'c')
				ft_putchar_fd(va_arg(ap, int), 2);
			else if (*msg == 's')
				ft_putstr_fd(va_arg(ap, char*), 2);
			else if (*msg == 'd')
				ft_putnbr_base_fd(va_arg(ap, int), 10, 2);
		}
		else
			ft_putchar_fd(*msg, 2);
		msg++;
	}
	va_end(ap);
	return (-42);
}
