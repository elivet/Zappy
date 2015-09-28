/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharpen <lcharpen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 22:17:03 by lcharpen          #+#    #+#             */
/*   Updated: 2014/06/26 22:17:22 by lcharpen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "serveur.h"
#include <time.h>
#include <stdio.h>

int				assign_team(t_server *serv, char *team, int actual)
{
	int		i;

	i = 0;
	while (serv->team[i])
	{
		if (!ft_strcmp(serv->team[i], team))
		{
			serv->clients[actual].team = serv->team[i];
			return (1);
		}
		i++;
	}
	write_client(serv->clients[actual].sock, "ko");
	return (-1);
}

static void		fill(t_server *serv, int coef, enum e_res res)
{
	int		i;
	int		rand_x;
	int		rand_y;

	i = 0;
	while (i++ < coef)
	{
		rand_y = rand() % serv->map.y;
		rand_x = rand() % serv->map.x;
		serv->map.map[rand_y][rand_x].res[res]++;
		serv->map.map[rand_y][rand_x].nbr++;
	}
}

static void		fill_map(t_server *serv)
{
	int		coef;

	coef = serv->max_clients * (int)ft_tabsize((void **)serv->team);
	serv->max_food = 25 * coef;
	fill(serv, 25 * coef, NOURRITURE);
	fill(serv, 13 * coef, LINEMATE);
	fill(serv, 12 * coef, DERAUMERE);
	fill(serv, 7 * coef, MENDIANE);
	fill(serv, 9 * coef, PHIRAS);
	fill(serv, 15 * coef, SIBUR);
	fill(serv, 2 * coef, THYSTAME);
}

void			create_map(t_server *serv)
{
	int		y;
	int		x;

	y = 0;
	serv->map.map = (t_square **)ft_memalloc(sizeof(t_square*) * serv->map.y);
	while (y < serv->map.y)
	{
		serv->map.map[y] = (t_square*)ft_memalloc(sizeof(t_square)
			* serv->map.x);
		x = -1;
		while (x++ < serv->map.x)
		{
			serv->map.map[y][x].nbr = 0;
			serv->map.map[y][x].res[NOURRITURE] = 0;
			serv->map.map[y][x].res[LINEMATE] = 0;
			serv->map.map[y][x].res[DERAUMERE] = 0;
			serv->map.map[y][x].res[SIBUR] = 0;
			serv->map.map[y][x].res[MENDIANE] = 0;
			serv->map.map[y][x].res[PHIRAS] = 0;
			serv->map.map[y][x].res[THYSTAME] = 0;
		}
		y++;
	}
	fill_map(serv);
}
