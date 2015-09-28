/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/21 19:46:35 by dsousa            #+#    #+#             */
/*   Updated: 2014/06/26 12:54:50 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

t_cmd	g_cmd[13] =
{
	{"avance", &cmd_avance, 7},
	{"droite", &cmd_droite, 7},
	{"gauche", &cmd_gauche, 7},
	{"voir", &cmd_voir, 7},
	{"prend ", &cmd_prendre, 7},
	{"pose ", &cmd_poser, 7},
	{"inventaire", &cmd_inventaire, 1},
	{"expulse", &cmd_expulse, 7},
	{"connect_nbr", &connect_nbr, 0},
	{"fork", &cmd_fork, 42},
	{"incantation", &cmd_incantation, 300},
	{"broadcast ", &cmd_broadcast, 7},
	{NULL, NULL, 0}
};

void		ft_cmd(t_server *serv, char *buff, int actual)
{
	int				i;

	i = 0;
	while (g_cmd[i].cmd)
	{
		if (!ft_strncmp(g_cmd[i].cmd, buff, ft_strlen(g_cmd[i].cmd)))
		{
			if (!ft_strcmp(buff, "fork") && serv->gfx.sock)
				pfk(serv->gfx.sock, &serv->clients[actual]);
			ft_wait(serv, &g_cmd[i], actual, buff);
			break ;
		}
		i++;
	}
	if (!g_cmd[i].cmd)
		write_client(serv->clients[actual].sock, "ko");
}

int			choose_k(t_server *serv, int dest, double x, double y)
{
	int		k;

	k = 0;
	if (x < serv->clients[dest].x && y > serv->clients[dest].y)
		k = 4;
	else if (x > serv->clients[dest].x && y > serv->clients[dest].y)
		k = 6;
	else if (x < serv->clients[dest].x && y < serv->clients[dest].y)
		k = 2;
	else if (x > serv->clients[dest].x && y < serv->clients[dest].y)
		k = 8;
	k += 2 * (serv->clients[dest].dir);
	if (k > 8)
		k -= 8;
	return (k);
}
