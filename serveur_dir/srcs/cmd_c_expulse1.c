/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_c_expulse1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 14:52:17 by jflorimo          #+#    #+#             */
/*   Updated: 2014/06/26 17:18:09 by lcharpen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

int			g_r[4][4] =
{
	{5, 1, 7, 3},
	{1, 5, 3, 7},
	{7, 3, 1, 5},
	{5, 1, 7, 3}
};

int			find_client_to_expulse(t_server *serv, int actual, int *client)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	j = 0;
	x = serv->clients[actual].x;
	y = serv->clients[actual].y;
	while (i <= serv->connected)
	{
		if (serv->clients[i].x == x && serv->clients[i].y == y && i != actual)
		{
			client[j] = i;
			j++;
		}
		i++;
	}
	return (j);
}

static int	expulser(int *v, int *r)
{
	int	ret;

	if (v[0] == v[2] && v[1] > v[3])
		ret = r[0];
	else if (v[0] == v[2] && v[1] < v[3])
		ret = r[1];
	else if (v[0] > v[2] && v[1] == v[3])
		ret = r[2];
	else
		ret = r[3];
	return (ret);
}

int			expulser_direction(t_server *serv, int actual, int who)
{
	int	v[4];

	v[0] = serv->clients[actual].x;
	v[1] = serv->clients[actual].y;
	v[2] = serv->clients[who].x;
	v[3] = serv->clients[who].y;
	if (serv->clients[who].dir % 2 == 0)
	{
		if (!serv->clients[who].dir)
			return (expulser(v, g_r[0]));
		else
			return (expulser(v, g_r[1]));
	}
	else
	{
		if (serv->clients[who].dir == 1)
			return (expulser(v, g_r[2]));
		else
			return (expulser(v, g_r[3]));
	}
	return (0);
}
