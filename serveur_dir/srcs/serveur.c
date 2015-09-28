/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elivet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 20:45:32 by elivet            #+#    #+#             */
/*   Updated: 2014/06/26 20:45:36 by elivet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include "../includes/serveur.h"
#include <time.h>

static int			init_connection(int port)
{
	int				sock;
	t_sockaddr_in	sin;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		exit_error("socket");
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	if (bind(sock, (t_sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
		exit_error("bind");
	if (listen(sock, MAX_CLIENTS) == SOCKET_ERROR)
		exit_error("listen");
	return (sock);
}

void				usage(void)
{
	ft_putstr("Usage: ./serveur -p <port> -x <width> -y <height> ");
	ft_putendl("-n <team> [<team>] [<team>] ... -c <nb> -t <t>");
	ft_putendl("\t-p numero de port");
	ft_putendl("\t-x largeur du Monde");
	ft_putendl("\t-y hauteur du Monde");
	ft_putendl("\t-n nom\\_equipe\\_1 nom\\_\\_equipe_2 ...");
	ft_putendl("\t-c nombre de client autorises au commencement du jeu");
	ft_putstr("\t-t diviseur de l'unite de temps ");
	ft_putendl("(plus t est grand, plus le jeu va vite)");
}

int					check_args(t_server *serv)
{
	int				s;
	int				x;
	int				y;

	s = serv->max_clients;
	x = serv->map.x;
	y = serv->map.y;
	if (serv->port > 0 && x > 0 && serv->map.y > 0 && s > 0 && serv->t > 0)
		return (1);
	return (0);
}

int					main(int argc, char *argv[])
{
	int				sock;
	int				gfxsock;
	t_server		*serv;

	srand(time(NULL));
	serv = (t_server *)ft_memalloc(sizeof(t_server));
	serv->argc = argc;
	if (serv->argc < 13 || parse_param(argv, serv) == -1)
	{
		usage();
		exit(-1);
	}
	sock = init_connection(serv->port);
	gfxsock = init_connection(serv->port + 1);
	server(sock, gfxsock, serv);
	return (0);
}
