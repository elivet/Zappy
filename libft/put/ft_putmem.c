/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/01 12:48:53 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/14 17:25:29 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putmem(void *adr)
{
	write(1, "0x", 2);
	ft_putnbr_base((size_t)adr, 16);
}

void	ft_putmem_fd(void *adr, size_t fd)
{
	write(fd, "0x", 2);
	ft_putnbr_base_fd((size_t)adr, 16, fd);
}
