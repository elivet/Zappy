/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_c_incantation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 15:19:08 by jflorimo          #+#    #+#             */
/*   Updated: 2014/06/26 17:34:32 by lcharpen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

void		cmd_incantation(t_server *serv, int actual, char *buff)
{
	int		i;

	i = 0;
	(void)buff;
	if (!verif_lvl_tb(serv, actual))
	{
		if (serv->gfx.sock)
		{
			pie(serv->gfx.sock, serv->clients[actual].x,
					serv->clients[actual].y, 0);
			while (i < serv->connected)
				plv(serv->gfx.sock, &serv->clients[i++]);
			mct(serv->gfx.sock, serv);
		}
		write(serv->clients[actual].sock, "ko\n", 3);
		return ;
	}
	lvl_up_player(serv, actual, serv->clients[actual].x,
			serv->clients[actual].y);
}

void		cmd_pre_incantation(t_server *serv, int actual, char *buff)
{
	int		i;
	int		level;
	int		x;
	int		y;

	(void)buff;
	x = serv->clients[actual].x;
	y = serv->clients[actual].y;
	i = 0;
	level = serv->clients[actual].lvl;
	if (!verif_lvl_tb(serv, actual))
		return ;
	while (i < serv->connected)
	{
		if (serv->gfx.sock)
			pic(serv->gfx.sock, actual, serv);
		if (serv->clients[i].x == x && serv->clients[i].y == y &&
				level == serv->clients[i].lvl)
			write_client(serv->clients[i].sock, "elevation en cours");
		i++;
	}
}
