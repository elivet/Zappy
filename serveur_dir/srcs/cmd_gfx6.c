/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_gfx6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharpen <lcharpen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 14:18:43 by lcharpen          #+#    #+#             */
/*   Updated: 2014/06/26 14:18:45 by lcharpen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "serveur.h"

void		pic(int csock, int actual, t_server *serv)
{
	char	*msg;
	int		i;

	i = -1;
	msg = ft_trunc("pic %d %d %d #%d", \
					serv->clients[actual].x, \
					serv->clients[actual].y, \
					serv->clients[actual].lvl, \
					serv->clients[actual].sock);
	while (serv->clients[++i].sock)
	{
		if ((actual != i) &&
			(serv->clients[actual].x == serv->clients[i].x) &&
			(serv->clients[actual].y == serv->clients[i].y))
			msg = ft_trunc("%s #%d", msg, serv->clients[actual].sock);
	}
	write_client(csock, msg);
	free(msg);
}

void		msz(int csock, t_map *map)
{
	char	*msg;

	msg = ft_trunc("msz %d %d", \
					map->x, \
					map->y);
	write_client(csock, msg);
	free(msg);
}
