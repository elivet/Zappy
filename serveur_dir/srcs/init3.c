/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elivet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 20:48:10 by elivet            #+#    #+#             */
/*   Updated: 2014/06/26 20:48:12 by elivet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include "../includes/serveur.h"
#include <time.h>

void			init_fds(t_server *server, int actual)
{
	int			i;

	i = 0;
	FD_ZERO(&(server->rdfs));
	FD_SET(server->sock, &(server->rdfs));
	FD_SET(server->gfxsock, &(server->rdfs));
	while (i < actual)
	{
		FD_SET(server->clients[i].sock, &(server->rdfs));
		i++;
	}
	if (server->gfx.sock)
		FD_SET(server->gfx.sock, &(server->rdfs));
}

static void		init_server_loop(t_server *server)
{
	int		i;
	int		j;

	i = 0;
	while (server->team[i])
	{
		server->teams[i].name = ft_strdup(server->team[i]);
		server->teams[i].eggs = 0;
		server->teams[i].baby = 0;
		j = 0;
		while (j < MAX_CLIENTS)
		{
			server->teams[i].egg_x[j] = -1;
			server->teams[i].egg_y[j] = -1;
			server->teams[i].time[j] = -1;
			server->teams[i].id[j] = 0;
			j++;
		}
		i++;
	}
}

void			init_server(t_server *server, int gfxsock, int sock)
{
	server->sock = sock;
	server->gfxsock = gfxsock;
	server->max = (sock < gfxsock) ? gfxsock : sock;
	server->connected = 0;
	server->gfx.sock = 0;
	create_map(server);
	init_server_loop(server);
}

void			init_eggs(t_server *server)
{
	int		i;
	int		j;
	int		save;

	i = 0;
	server->num_egg = 0;
	while (i < MAX_CLIENTS && server->team[i])
	{
		if (server->teams[i].eggs)
		{
			j = 0;
			while (j < MAX_CLIENTS)
			{
				save = server->teams[i].time[j];
				if (save != -1 && save < (double)(clock() / CLOCKS_PER_SEC))
				{
					server->teams[i].baby++;
					server->teams[i].eggs--;
					server->teams[i].time[j] = -1;
				}
				j++;
			}
		}
		i++;
	}
}

void			init_time(t_server *server, int *actual)
{
	int		i;
	int		save;

	i = 0;
	(void)server;
	while (i < server->connected)
	{
		save = ((double)clock() / CLOCKS_PER_SEC) - server->clients[i].time;
		if (save >= (double)(126 / server->t))
		{
			if (server->clients[i].inventaire.res[NOURRITURE] <= 0)
			{
				write_client(server->clients[i].sock, "mort");
				remove_client(server, i, actual);
			}
			else
			{
				server->clients[i].inventaire.res[NOURRITURE]--;
				server->clients[i].time = (double)clock() / CLOCKS_PER_SEC;
			}
		}
		i++;
	}
}
