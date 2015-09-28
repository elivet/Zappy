/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 15:26:54 by jflorimo          #+#    #+#             */
/*   Updated: 2014/06/26 17:49:06 by lcharpen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

void			cmd_inventaire(t_server *serv, int actual, char *buff)
{
	char	*str;

	(void)buff;
	str = ft_trunc("{nourriture %d, sibur %d, phiras %d, mendiane %d", \
	serv->clients[actual].inventaire.res[NOURRITURE], \
	serv->clients[actual].inventaire.res[SIBUR], \
	serv->clients[actual].inventaire.res[PHIRAS], \
	serv->clients[actual].inventaire.res[MENDIANE]);
	str = ft_trunc("%s, thystame %d, deraumere %d, linemate %d}", \
	str, \
	serv->clients[actual].inventaire.res[THYSTAME], \
	serv->clients[actual].inventaire.res[DERAUMERE], \
	serv->clients[actual].inventaire.res[LINEMATE]);
	write_client(serv->clients[actual].sock, str);
	free(str);
}

static int		findcase1(t_server *serv, int dest, int src)
{
	double		x;

	if (serv->clients[src].y < serv->clients[dest].y)
	{
		x = (int)(1 + 2 * (serv->clients[dest].dir));
		if (x > 8)
			x -= 8;
		return ((int)x);
	}
	else
	{
		x = (int)(5 + 2 * (serv->clients[dest].dir));
		if (x > 8)
			x -= 8;
		return ((int)x);
	}
}

static int		findcase2(t_server *serv, int dest, int src)
{
	double		x;

	if (serv->clients[src].x < serv->clients[dest].x)
	{
		x = (int)(3 + 2 * (serv->clients[dest].dir));
		if (x > 8)
			x -= 8;
		return ((int)x);
	}
	else
	{
		x = (int)(7 + 2 * (serv->clients[dest].dir));
		if (x > 8)
			x -= 8;
		return ((int)x);
	}
}

int				findcase(t_server *serv, int dest, int src)
{
	double		x;
	double		y;
	double		xdest;
	double		ydest;
	double		coef;

	xdest = (double)serv->clients[dest].x;
	ydest = (double)serv->clients[dest].y;
	x = xdest - (double)serv->clients[src].x;
	y = ydest - (double)serv->clients[src].y;
	if ((serv->clients[dest].x - serv->clients[src].x) == 0 &&
		(serv->clients[dest].y - serv->clients[src].y) == 0)
		return (0);
	else if ((serv->clients[dest].x - serv->clients[src].x) == 0)
		return (findcase1(serv, dest, src));
	else if ((serv->clients[dest].y - serv->clients[src].y) == 0)
		return (findcase2(serv, dest, src));
	coef = y / x;
	x = xdest > serv->clients[src].x ? xdest - 1 : xdest + 1;
	y = xdest > serv->clients[src].x ? ydest - coef : ydest + coef;
	return (choose_k(serv, dest, x, y));
}
