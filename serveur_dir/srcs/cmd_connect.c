/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_connect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 13:40:53 by jflorimo          #+#    #+#             */
/*   Updated: 2014/06/26 13:40:54 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

int			is_egg_connect(t_server *serv, int actual)
{
	int		i;
	int		nb;

	nb = 0;
	i = 0;
	while (i < serv->connected)
	{
		if (serv->clients[i].team && !ft_strcmp(serv->clients[i].team,
			serv->clients[actual].team))
			nb++;
		i++;
	}
	if (nb <= serv->max_clients)
		return (serv->teams[i].eggs);
	return (0);
}

int			get_nbr(t_server *serv, int actual)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (i < serv->connected)
	{
		if (serv->clients[i].team && !ft_strcmp(serv->clients[i].team,
			serv->clients[actual].team))
			nb++;
		i++;
	}
	return (nb);
}

void		connect_nbr(t_server *serv, int actual, char *buff)
{
	int		i;
	int		nb;
	char	*tmp;
	int		eggs;

	(void)buff;
	i = 0;
	nb = get_nbr(serv, actual);
	eggs = 0;
	while (i < MAX_CLIENTS && serv->teams[i].name &&
		ft_strcmp(serv->teams[i].name, serv->clients[actual].team))
		i++;
	if (i < MAX_CLIENTS && serv->teams[i].name)
		eggs = serv->teams[i].baby;
	if ((serv->max_clients - nb) + eggs < 0)
	{
		write_client(serv->clients[actual].sock, "ko");
		return ;
	}
	tmp = ft_itoa((serv->max_clients - nb) + eggs);
	write_client(serv->clients[actual].sock, tmp);
	free(tmp);
}
