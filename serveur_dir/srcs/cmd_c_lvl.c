/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_c_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 15:18:25 by jflorimo          #+#    #+#             */
/*   Updated: 2014/06/26 15:18:25 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

int	g_nb[7][7] =
{
	{1, 1, 0, 0, 0, 0, 0},
	{2, 1, 1, 1, 0, 0, 0},
	{2, 2, 0, 1, 0, 2, 0},
	{4, 1, 1, 2, 0, 1, 0},
	{4, 1, 2, 1, 3, 0, 0},
	{6, 2, 2, 3, 0, 1, 0},
	{6, 2, 2, 2, 2, 2, 1}
};

int		verif_lvl_tb(t_server *serv, int actual)
{
	int	nbr;
	int	i;
	int	x;

	nbr = 0;
	i = 0;
	x = serv->clients[actual].x;
	nbr = count_player(serv, actual, x, serv->clients[actual].y);
	if (nbr == g_nb[serv->clients[actual].lvl - 1][i])
	{
		while (i < 6)
		{
			i++;
			if (g_nb[serv->clients[actual].lvl - 1][i] > 0)
			{
				if ((int)serv->map.map[serv->clients[actual].y][x].res[i]
					< g_nb[serv->clients[actual].lvl - 1][i])
					return (0);
			}
		}
	}
	else
		return (0);
	return (1);
}

void	do_lvl_up(t_server *serv, int i)
{
	char	*lvl;

	serv->clients[i].lvl++;
	plv(serv->gfx.sock, &serv->clients[i]);
	lvl = ft_itoa(serv->clients[i].lvl);
	lvl = ft_strjoin("niveau actuel : ", lvl);
	write_client(serv->clients[i].sock, lvl);
	free(lvl);
}

void	lvl_up_player(t_server *serv, int actual, int x, int y)
{
	int		i;
	int		level;
	int		ok;

	i = 0;
	ok = 0;
	level = serv->clients[actual].lvl;
	pie(serv->gfx.sock, x, y, 1);
	while (i < serv->connected)
	{
		if (serv->clients[i].x == x && serv->clients[i].y == y &&
		level == serv->clients[i].lvl)
		{
			do_lvl_up(serv, i);
			ok++;
		}
		i++;
	}
	if (ok > 0)
		expulse_item(serv, actual, g_nb[serv->clients[actual].lvl - 2]);
	mct(serv->gfx.sock, serv);
}
