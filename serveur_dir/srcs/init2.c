/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elivet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 20:47:50 by elivet            #+#    #+#             */
/*   Updated: 2014/06/26 20:47:53 by elivet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "serveur.h"
#include <time.h>
#include <stdio.h>

void		init_gfx_boucle_clients(t_server *serv, int csock)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (serv->teams[i].name)
		{
			j = 0;
			while (serv->teams[i].egg_x[j] != -1)
				j++;
			j--;
			printf("%d : %d : %d\n", j, serv->teams[i].eggs,
				serv->teams[i].egg_x[j]);
			while (j >= serv->teams[i].baby
				&& serv->teams[i].egg_x[j] != -1
				&& serv->teams[i].egg_y[j] != -1)
			{
				printf("%d : %d : %d\n", j, serv->teams[i].eggs,
					serv->teams[i].egg_x[j]);
				enw(csock, &serv->teams[i], j--, 0);
			}
		}
		i++;
	}
}

void		init_gfx(t_server *serv, int csock)
{
	int		i;
	char	*msg;

	msg = ft_trunc("msz %d %d", serv->map.x, serv->map.y);
	write_client(csock, msg);
	free(msg);
	msg = ft_trunc("sgt %d", serv->t);
	write_client(csock, msg);
	free(msg);
	mct(csock, serv);
	tna(csock, serv);
	i = 0;
	while (i < serv->connected)
	{
		pnw(csock, &serv->clients[i]);
		i++;
	}
	init_gfx_boucle_clients(serv, csock);
}

void		init_client(t_server *serv, int actual)
{
	int		i;

	serv->clients[actual].x = rand() % serv->map.x;
	serv->clients[actual].y = rand() % serv->map.y;
	serv->clients[actual].dir = (rand() % 4);
	serv->clients[actual].lvl = 1;
	serv->clients[actual].inventaire.res[NOURRITURE] = 9;
	serv->clients[actual].inventaire.res[LINEMATE] = 0;
	serv->clients[actual].inventaire.res[DERAUMERE] = 0;
	serv->clients[actual].inventaire.res[SIBUR] = 0;
	serv->clients[actual].inventaire.res[MENDIANE] = 0;
	serv->clients[actual].inventaire.res[PHIRAS] = 0;
	serv->clients[actual].inventaire.res[THYSTAME] = 0;
	serv->clients[actual].last_cmd_end = 0;
	serv->clients[actual].time = (double)clock() / CLOCKS_PER_SEC;
	i = 0;
	while (i < 10)
	{
		serv->clients[actual].queue[i].cmd = NULL;
		serv->clients[actual].queue[i].exe_time = 0;
		i++;
	}
}
