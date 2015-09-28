/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_gfx4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharpen <lcharpen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 14:18:18 by lcharpen          #+#    #+#             */
/*   Updated: 2014/06/26 14:18:20 by lcharpen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "serveur.h"

void		pin(int csock, t_client *client)
{
	char	*msg;

	msg = ft_trunc("pin #%d %d %d %d %d %d %d %d %d %d", \
		client->sock, \
		client->x, \
		client->y, \
		client->inventaire.res[NOURRITURE], \
		client->inventaire.res[LINEMATE], \
		client->inventaire.res[DERAUMERE], \
		client->inventaire.res[SIBUR], \
		client->inventaire.res[MENDIANE], \
		client->inventaire.res[PHIRAS], \
		client->inventaire.res[THYSTAME]);
	write_client(csock, msg);
	free(msg);
}

void		cmd_gfx(t_server *serv, char *buff)
{
	(void)serv;
	(void)buff;
}

void		plv(int csock, t_client *client)
{
	char	*msg;

	msg = ft_trunc("plv #%d %d", \
					client->sock, \
					client->lvl);
	write_client(csock, msg);
	free(msg);
}

void		pie(int csock, int x, int y, int r)
{
	char	*msg;

	msg = ft_trunc("pie %d %d %d", \
					x, \
					y, \
					r);
	write_client(csock, msg);
	free(msg);
}

void		pdi(int csock, t_client *client)
{
	char	*msg;

	msg = ft_trunc("pdi #%d", client->sock);
	write_client(csock, msg);
	free(msg);
}
