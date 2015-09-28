/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prendre.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharpen <lcharpen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/21 12:44:56 by lcharpen          #+#    #+#             */
/*   Updated: 2014/06/26 13:31:58 by lcharpen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"
#include <stdio.h>

static void		prend(t_server *serv, int actual, enum e_res res)
{
	serv->map.map[serv->clients[actual].y][serv->clients[actual].x].res[res]--;
	serv->map.map[serv->clients[actual].y][serv->clients[actual].x].nbr--;
	serv->clients[actual].inventaire.res[res]++;
	serv->clients[actual].inventaire.nbr++;
	write_client(serv->clients[actual].sock, "ok");
	if (serv->gfx.sock)
	{
		pgt(serv->gfx.sock, &(serv->clients[actual]), res);
		pin(serv->gfx.sock, &(serv->clients[actual]));
		bct(serv->gfx.sock, serv, serv->clients[actual].x,
			serv->clients[actual].y);
	}
}

static	void	cmd_prendre_prendre2(t_server *serv, int actual, char *arg)
{
	if (!ft_strcmp(arg, "sibur") && serv->map.map
		[serv->clients[actual].y][serv->clients[actual].x].res[SIBUR] > 0)
		prend(serv, actual, SIBUR);
	else if (!ft_strcmp(arg, "mendiane") && serv->map.map
		[serv->clients[actual].y][serv->clients[actual].x].res[MENDIANE] > 0)
		prend(serv, actual, MENDIANE);
	else if (!ft_strcmp(arg, "phiras") && serv->map.map
		[serv->clients[actual].y][serv->clients[actual].x].res[PHIRAS] > 0)
		prend(serv, actual, PHIRAS);
	else if (!ft_strcmp(arg, "thystame") && serv->map.map
		[serv->clients[actual].y][serv->clients[actual].x].res[THYSTAME] > 0)
		prend(serv, actual, THYSTAME);
	else if (!ft_strcmp(arg, "nourriture") && serv->map.map
		[serv->clients[actual].y][serv->clients[actual].x].res[NOURRITURE] > 0)
		prend(serv, actual, NOURRITURE);
	else
		write_client(serv->clients[actual].sock, "ko");
}

void			cmd_prendre(t_server *serv, int actual, char *buff)
{
	char	**arg;

	if (serv->map.map[serv->clients[actual].y][serv->clients[actual].x].nbr > 0)
	{
		arg = ft_strsplit(buff, ' ');
		if (arg[1])
		{
			if (!ft_strcmp(arg[1], "linemate") && serv->map.map
				[serv->clients[actual].y]
				[serv->clients[actual].x].res[LINEMATE] > 0)
				prend(serv, actual, LINEMATE);
			else if (!ft_strcmp(arg[1], "deraumere") && serv->map.map
				[serv->clients[actual].y]
				[serv->clients[actual].x].res[DERAUMERE] > 0)
				prend(serv, actual, DERAUMERE);
			else
				cmd_prendre_prendre2(serv, actual, arg[1]);
		}
		ft_freetab((void **)arg);
	}
	else
		write_client(serv->clients[actual].sock, "ko");
}
