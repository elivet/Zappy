/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_c_expulse2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 14:52:38 by jflorimo          #+#    #+#             */
/*   Updated: 2014/06/26 15:49:21 by lcharpen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

static void	cmd_expulse2(t_server *serv, int actual, int who)
{
	int		add;

	add = serv->clients[actual].dir == 2 ? 1 : -1;
	serv->clients[who].y += add;
	serv->clients[who].y = serv->clients[who].y >= serv->map.y
	? 0 : serv->clients[who].y;
	serv->clients[who].y = serv->clients[who].y < 0
	? serv->map.y - 1 : serv->clients[who].y;
}

static void	cmd_expulse3(t_server *serv, int actual, int who)
{
	int		add;

	add = serv->clients[actual].dir == 1 ? 1 : -1;
	serv->clients[who].x += add;
	serv->clients[who].x = serv->clients[who].x >= serv->map.x
	? 0 : serv->clients[who].x;
	serv->clients[who].x = serv->clients[who].x < 0
	? serv->map.x - 1 : serv->clients[who].x;
}

static void	cmd_expulse4(t_server *serv, int actual, int who)
{
	int		ret;
	char	*str;

	ret = expulser_direction(serv, actual, who);
	str = ft_trunc("deplacement %d", ret);
	write_client(serv->clients[who].sock, str);
}

void		cmd_expulse(t_server *serv, int actual, char *buff)
{
	int		*who;
	int		i;
	int		j;

	(void)buff;
	i = 0;
	who = (int *)ft_memalloc(sizeof(int) * serv->connected);
	j = find_client_to_expulse(serv, actual, who);
	while (i < j)
	{
		if (serv->clients[actual].dir % 2 == 0)
			cmd_expulse2(serv, actual, who[i]);
		else
			cmd_expulse3(serv, actual, who[i]);
		if (serv->gfx.sock)
			ppo(serv->gfx.sock, &serv->clients[who[i]]);
		cmd_expulse4(serv, actual, who[i]);
		i++;
	}
	if (j == 0)
		write_client(serv->clients[actual].sock, "ko");
	else
		write_client(serv->clients[actual].sock, "ok");
}

void		expulse_item(t_server *serv, int actual, int *nb)
{
	int		i;
	int		j;

	i = 0;
	while (i < 6)
	{
		i++;
		if (nb[i] > 0)
		{
			serv->map.map[serv->clients[actual].y][serv->clients[actual].x].
				res[i]--;
			j = serv->clients[actual].x >= serv->map.x
			? 0 : serv->clients[actual].x + 1;
			serv->map.map[serv->clients[actual].y][j].res[i]++;
		}
	}
}
