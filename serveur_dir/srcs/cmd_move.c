/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 14:18:17 by jflorimo          #+#    #+#             */
/*   Updated: 2014/06/26 14:56:23 by lcharpen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

static void	cmd_avance2(t_server *serv, int actual)
{
	if (serv->gfx.sock)
		ppo(serv->gfx.sock, &serv->clients[actual]);
	write_client(serv->clients[actual].sock, "ok");
	printf("YOUR POSITION IS NOW: x: %d y: %d dir:%d\n",
		serv->clients[actual].x, serv->clients[actual].y,
		serv->clients[actual].dir);
	printf("player %d avance\n", actual);
}

void		cmd_avance(t_server *serv, int actual, char *buff)
{
	int		add;

	(void)buff;
	printf("YOUR POSITION IS: x: %d y: %d dir:%d\n", serv->clients[actual].x,
		serv->clients[actual].y, serv->clients[actual].dir);
	if (serv->clients[actual].dir % 2 == 0)
	{
		add = serv->clients[actual].dir == 2 ? 1 : -1;
		serv->clients[actual].y += add;
		serv->clients[actual].y = serv->clients[actual].y >= serv->map.y
		? 0 : serv->clients[actual].y;
		serv->clients[actual].y = serv->clients[actual].y < 0
		? serv->map.y - 1 : serv->clients[actual].y;
	}
	else
	{
		add = serv->clients[actual].dir == 1 ? 1 : -1;
		serv->clients[actual].x += add;
		serv->clients[actual].x = serv->clients[actual].x >= serv->map.x
		? 0 : serv->clients[actual].x;
		serv->clients[actual].x = serv->clients[actual].x < 0
		? serv->map.x - 1 : serv->clients[actual].x;
	}
	cmd_avance2(serv, actual);
}

void		cmd_droite(t_server *serv, int actual, char *buff)
{
	(void)buff;
	serv->clients[actual].dir = (serv->clients[actual].dir + 1) % 4;
	if (serv->gfx.sock)
		ppo(serv->gfx.sock, &serv->clients[actual]);
	write_client(serv->clients[actual].sock, "ok");
}

void		cmd_gauche(t_server *serv, int actual, char *buff)
{
	if ((serv->clients[actual].dir - 1) == -1)
		serv->clients[actual].dir = 3;
	else
		serv->clients[actual].dir--;
	if (serv->gfx.sock)
		ppo(serv->gfx.sock, &serv->clients[actual]);
	write_client(serv->clients[actual].sock, "ok");
	(void)buff;
}
