/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regen_food.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elivet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 20:49:14 by elivet            #+#    #+#             */
/*   Updated: 2014/06/26 20:49:17 by elivet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serveur.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include "../../libft/libft.h"

int			count_food_on_map(t_server *serv)
{
	int		x;
	int		y;
	int		count;

	count = 0;
	y = 0;
	while (y < serv->map.y)
	{
		x = 0;
		while (x < serv->map.x)
		{
			count = count + serv->map.map[y][x].res[NOURRITURE];
			x++;
		}
		y++;
	}
	return (count);
}

void		get_food(int y, int x, t_server *serv)
{
	int			alea;

	if (count_food_on_map(serv) <= serv->max_food - 4)
	{
		alea = rand() % 5;
		serv->map.map[y][x].res[NOURRITURE] =
		serv->map.map[y][x].res[NOURRITURE] + alea;
		serv->map.map[y][x].nbr = serv->map.map[y][x].nbr + alea;
	}
}

void		regen_food_two(t_server *serv)
{
	int				x;
	int				y;

	x = serv->map.x - 1;
	while (x >= 0)
	{
		y = serv->map.y - 1;
		while (y >= 0)
		{
			get_food(y, x, serv);
			y--;
		}
		x--;
	}
}

void		get_food_serv(t_server *serv, int x, int y)
{
	while (x < serv->map.x)
	{
		get_food(y, x, serv);
		x++;
	}
}

void		regen_food(t_server *serv)
{
	int				x;
	int				y;
	int				p;
	static int		i = 0;

	p = (serv->max_food / 100) * 50;
	if (count_food_on_map(serv) <= p)
	{
		if (i % 2 == 0)
		{
			y = 0;
			while (y < serv->map.y)
			{
				x = 0;
				get_food_serv(serv, x, y);
				y++;
			}
		}
		else
			regen_food_two(serv);
		i++;
	}
}
