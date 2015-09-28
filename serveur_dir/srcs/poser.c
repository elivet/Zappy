/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharpen <lcharpen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/21 12:56:53 by lcharpen          #+#    #+#             */
/*   Updated: 2014/06/26 13:40:49 by lcharpen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include <libft.h>

void		poser(t_server *serv, int actual, enum e_res res)
{
	serv->clients[actual].inventaire.res[res]--;
	serv->map.map[serv->clients[actual].y][serv->clients[actual].x].res[res]++;
	serv->map.map[serv->clients[actual].y][serv->clients[actual].x].nbr++;
	write_client(serv->clients[actual].sock, "ok");
	if (serv->gfx.sock)
	{
		pdr(serv->gfx.sock, &serv->clients[actual], res);
		pin(serv->gfx.sock, &serv->clients[actual]);
		bct(serv->gfx.sock, serv, serv->clients[actual].x,
			serv->clients[actual].y);
	}
}

void		cmd_poser_arg(t_server *serv, int actual, char **arg)
{
	if (!ft_strcmp(arg[1], "linemate") &&
		serv->clients[actual].inventaire.res[LINEMATE] > 0)
		poser(serv, actual, LINEMATE);
	else if (!ft_strcmp(arg[1], "deraumere") &&
		serv->clients[actual].inventaire.res[DERAUMERE] > 0)
		poser(serv, actual, DERAUMERE);
	else if (!ft_strcmp(arg[1], "sibur") &&
		serv->clients[actual].inventaire.res[SIBUR] > 0)
		poser(serv, actual, SIBUR);
	else if (!ft_strcmp(arg[1], "mendiane") &&
		serv->clients[actual].inventaire.res[MENDIANE] > 0)
		poser(serv, actual, MENDIANE);
	else if (!ft_strcmp(arg[1], "phiras") &&
		serv->clients[actual].inventaire.res[PHIRAS] > 0)
		poser(serv, actual, PHIRAS);
	else if (!ft_strcmp(arg[1], "thystame") &&
		serv->clients[actual].inventaire.res[THYSTAME] > 0)
		poser(serv, actual, THYSTAME);
	else if (!ft_strcmp(arg[1], "nourriture") &&
		serv->clients[actual].inventaire.res[NOURRITURE] > 0)
		poser(serv, actual, NOURRITURE);
	else
		write_client(serv->clients[actual].sock, "ko");
}

void		cmd_poser(t_server *serv, int actual, char *buff)
{
	char	**arg;

	arg = ft_strsplit(buff, ' ');
	if (arg[1])
	{
		cmd_poser_arg(serv, actual, arg);
	}
	else
		write_client(serv->clients[actual].sock, "ko");
	ft_freetab((void **)arg);
}
