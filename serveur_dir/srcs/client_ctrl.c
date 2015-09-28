/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elivet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 14:21:55 by elivet            #+#    #+#             */
/*   Updated: 2014/06/26 14:21:59 by elivet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <string.h>
#include <stdio.h>
#include "../includes/serveur.h"

void		clear_clients(t_client *clients, int actual)
{
	int		i;

	i = 0;
	while (i < actual)
	{
		close(clients[i].sock);
		i++;
	}
}

void		welcome_client(t_server *server, int *actual, int csock)
{
	write_client(csock, "BIENVENUE");
	server->max = csock > server->max ? csock : server->max;
	server->clients[*actual].sock = csock;
	server->connected++;
}

void		new_client_gfx(t_server *server, int *actual, int csock)
{
	char	*tmp;
	int		egg;

	tmp = ft_trunc("%d %d", server->map.x, server->map.y);
	write_client(csock, tmp);
	free(tmp);
	init_client(server, *actual);
	if (server->gfx.sock && (egg = is_egg_connect(server, *actual)))
		ebo(server->gfx.sock, egg);
	if (server->gfx.sock)
		pnw(server->gfx.sock, &server->clients[*actual]);
	(*actual)++;
}

int			new_client(t_server *server, int *actual, char *buff)
{
	int				csock;
	t_sockaddr_in	csin;
	socklen_t		sinsize;

	sinsize = sizeof(csin);
	csock = accept(server->sock, (t_sockaddr *)&csin, &sinsize);
	printf("Connect %d\n", csock);
	if (csock == SOCKET_ERROR)
	{
		error("accept");
		return (-1);
	}
	welcome_client(server, actual, csock);
	if (read_client(csock, buff) == -1)
		return (-1);
	if (assign_team(server, buff, *actual) == -1)
		return (-1);
	FD_SET(csock, &(server->rdfs));
	if (connect_nbr_init(server, *actual, buff) < 0)
		return (-1);
	new_client_gfx(server, actual, csock);
	return (csock);
}

int			new_gfxclient(t_server *server, char *buff)
{
	int				csock;
	t_sockaddr_in	csin;
	socklen_t		sinsize;

	sinsize = sizeof(csin);
	csock = accept(server->gfxsock, (t_sockaddr *)&csin, &sinsize);
	printf("Connect %d\n", csock);
	if (csock == SOCKET_ERROR)
	{
		error("accept");
		return (-1);
	}
	write_client(csock, "BIENVENUE");
	if (read_client(csock, buff) == -1)
		return (-1);
	if (ft_strcmp("GRAPHIC", buff))
		return (-1);
	init_gfx(server, csock);
	server->max = csock > server->max ? csock : server->max;
	FD_SET(csock, &(server->rdfs));
	server->gfx.sock = csock;
	return (csock);
}
