/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_gfx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elivet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 20:46:46 by elivet            #+#    #+#             */
/*   Updated: 2014/06/26 20:46:48 by elivet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "serveur.h"

void		bct(int csock, t_server *serv, int x, int y)
{
	char	*msg;

	msg = ft_trunc("bct %d %d %d %d %d %d %d %d %d", x, y, \
		serv->map.map[y][x].res[NOURRITURE], \
		serv->map.map[y][x].res[LINEMATE], \
		serv->map.map[y][x].res[DERAUMERE], \
		serv->map.map[y][x].res[SIBUR], \
		serv->map.map[y][x].res[MENDIANE], \
		serv->map.map[y][x].res[PHIRAS], \
		serv->map.map[y][x].res[THYSTAME]);
	write_client(csock, msg);
	free(msg);
}

void		mct(int csock, t_server *serv)
{
	int		i;
	int		j;

	i = 0;
	while (i < serv->map.x)
	{
		j = 0;
		while (j < serv->map.y)
		{
			bct(csock, serv, i, j);
			j++;
		}
		i++;
	}
}

void		tna(int csock, t_server *serv)
{
	int		i;
	char	*msg;

	i = 0;
	while (serv->team[i])
	{
		msg = ft_trunc("tna %s", serv->team[i]);
		write_client(csock, msg);
		free(msg);
		i++;
	}
}

void		pnw(int csock, t_client *client)
{
	char	*msg;

	msg = ft_trunc("pnw #%d %d %d %d %d %s", \
		client->sock, \
		client->x, \
		client->y, \
		client->dir, \
		client->lvl, \
		client->team);
	write_client(csock, msg);
	free(msg);
}
