/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 14:51:21 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/21 14:52:36 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl(char *str)
{
	ft_putstr(str);
	write(1, "\n", 1);
}

void	ft_putendl_fd(char *str, size_t fd)
{
	ft_putstr_fd(str, fd);
	write(fd, "\n", 1);
}
