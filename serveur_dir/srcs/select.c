/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elivet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 20:45:53 by elivet            #+#    #+#             */
/*   Updated: 2014/06/26 20:45:54 by elivet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include "../includes/serveur.h"
#include <time.h>

void				do_cmd(t_server *server)
{
	int				i;
	int				j;
	int				save;
	char			*str;

	i = 0;
	while (i < server->connected)
	{
		j = 0;
		while (j < 10)
		{
			save = server->clients[i].queue[j].exe_time;
			if ((double)((double)clock() / (double)CLOCKS_PER_SEC) >= save
				&& server->clients[i].queue[j].cmd != NULL)
			{
				str = ft_strdup(server->clients[i].queue[j].arg);
				server->clients[i].queue[j].cmd->f(server, i, str);
				server->clients[i].queue[j].cmd = NULL;
				server->clients[i].queue[j].exe_time = 0;
				free(server->clients[i].queue[j].arg);
			}
			j++;
		}
		i++;
	}
}

static int			server_new_client(t_server *server, int *actual,
	char *buff)
{
	if (new_client(server, actual, buff) == -1)
	{
		server->connected--;
		return (1);
	}
	return (0);
}

static int			server_select(t_server *server, int *actual)
{
	char			buff[BUF_SIZE + 1];
	struct timeval	tv;

	tv.tv_sec = 0;
	tv.tv_usec = 1;
	if (select(server->max + 1, &server->rdfs, NULL, NULL, &tv) == -1)
		exit_error("select");
	else if (FD_ISSET(server->sock, &server->rdfs))
	{
		if (server_new_client(server, actual, buff))
			return (1);
	}
	else if (FD_ISSET(server->gfxsock, &server->rdfs))
	{
		if (new_gfxclient(server, buff) == -1)
		{
			server->gfx.sock = 0;
			return (1);
		}
	}
	else
		client_talking(server, actual, buff);
	return (0);
}

void				server(int sock, int gfxsock, t_server *server)
{
	int				actual;

	actual = 0;
	init_server(server, gfxsock, sock);
	while (1)
	{
		init_time(server, &actual);
		regen_food(server);
		do_cmd(server);
		init_eggs(server);
		init_fds(server, actual);
		if (server_select(server, &actual))
			continue ;
	}
	clear_clients(server->clients, actual);
	close(server->sock);
}
