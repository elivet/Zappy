/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elivet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 20:35:15 by elivet            #+#    #+#             */
/*   Updated: 2014/06/26 20:35:16 by elivet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

void		cmd_broadcast_loop(t_server *serv, int actual, char **tmp)
{
	int		k_case;
	int		i;
	char	*str;

	i = 0;
	while (i < serv->connected)
	{
		if (i != actual)
		{
			k_case = findcase(serv, i, actual);
			str = ft_trunc("message %d, %s", k_case, tmp[1]);
			write_client(serv->clients[i].sock, str);
			free(str);
		}
		i++;
	}
}

void		cmd_broadcast(t_server *serv, int actual, char *buff)
{
	char	**tmp;

	tmp = ft_strsplit(buff, ' ');
	if (!tmp[1])
	{
		write_client(serv->clients[actual].sock, "ko");
		return ;
	}
	write_client(serv->clients[actual].sock, "ok");
	if (serv->gfx.sock)
		pbc(serv->gfx.sock, tmp[1], &serv->clients[actual]);
	cmd_broadcast_loop(serv, actual, tmp);
	ft_freetab((void **)tmp);
}
