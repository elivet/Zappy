/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_gfx2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharpen <lcharpen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 14:17:48 by lcharpen          #+#    #+#             */
/*   Updated: 2014/06/26 14:17:50 by lcharpen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "serveur.h"

void		ppo(int csock, t_client *client)
{
	char	*msg;

	msg = ft_trunc("ppo #%d %d %d %d", \
		client->sock, \
		client->x, \
		client->y, \
		client->dir);
	write_client(csock, msg);
	free(msg);
}

void		pgt(int csock, t_client *client, enum e_res res)
{
	char	*msg;

	msg = ft_trunc("pgt #%d %d", \
		client->sock, \
		res);
	write_client(csock, msg);
	free(msg);
}

void		pdr(int csock, t_client *client, enum e_res res)
{
	char	*msg;

	msg = ft_trunc("pdr #%d %d", \
		client->sock, \
		res);
	write_client(csock, msg);
	free(msg);
}

void		pex(int csock, t_client *client)
{
	char	*msg;

	msg = ft_trunc("pex #%d", client->sock);
	write_client(csock, msg);
	free(msg);
}

void		pbc(int csock, char *buff, t_client *client)
{
	char	*msg;

	msg = ft_trunc("pbc #%d %s", client->sock, buff);
	write_client(csock, msg);
	free(msg);
}
