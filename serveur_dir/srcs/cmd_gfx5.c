/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_gfx5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharpen <lcharpen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 14:18:26 by lcharpen          #+#    #+#             */
/*   Updated: 2014/06/26 14:18:27 by lcharpen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "serveur.h"

void		pfk(int csock, t_client *client)
{
	char	*msg;

	msg = ft_trunc("pfk #%d", client->sock);
	write_client(csock, msg);
	free(msg);
}

void		eht(int csock, int num_egg)
{
	char	*msg;

	msg = ft_trunc("eht #%d", num_egg);
	write_client(csock, msg);
	free(msg);
}

void		ebo(int csock, int num_egg)
{
	char	*msg;

	msg = ft_trunc("ebo #%d", num_egg);
	write_client(csock, msg);
	free(msg);
}

void		edi(int csock, int num_egg)
{
	char	*msg;

	msg = ft_trunc("edi #%d", num_egg);
	write_client(csock, msg);
	free(msg);
}

void		sgt(int csock, time_t *tm)
{
	char	*msg;

	msg = ft_trunc("edi #%d", tm);
	write_client(csock, msg);
	free(msg);
}
