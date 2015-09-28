/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_ctrl2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elivet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 14:16:34 by elivet            #+#    #+#             */
/*   Updated: 2014/06/26 17:30:45 by lcharpen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <string.h>
#include <stdio.h>
#include "../includes/serveur.h"

int		connect_nbr_init_loops(t_server *serv, int *nb, char *buff)
{
	int		i;
	int		eggs;

	i = 0;
	eggs = 0;
	while (i < serv->connected)
	{
		if (serv->clients[i].team && !ft_strcmp(serv->clients[i].team, buff))
			(*nb)++;
		i++;
	}
	i = 0;
	while (i < MAX_CLIENTS && ft_strcmp(serv->teams[i].name, buff))
		i++;
	if (i < MAX_CLIENTS)
		eggs = serv->teams[i].baby;
	return (eggs);
}

int		connect_nbr_init(t_server *serv, int actual, char *buff)
{
	int		nb;
	char	*tmp;
	int		eggs;
	char	**arg;

	arg = ft_strsplit(buff, ' ');
	if (arg[1])
	{
		write_client(serv->clients[actual].sock, "ko");
		return (-1);
	}
	ft_freetab((void **)arg);
	nb = 0;
	eggs = connect_nbr_init_loops(serv, &nb, buff);
	if ((serv->max_clients - nb) + eggs < 0)
	{
		write_client(serv->clients[actual].sock, "ko");
		return (-1);
	}
	tmp = ft_itoa((serv->max_clients - nb) + eggs);
	write_client(serv->clients[actual].sock, tmp);
	free(tmp);
	return (0);
}

void	remove_client(t_server *serv, int rm, int *actual)
{
	t_client	*clt;
	int			i;
	int			save;

	i = -1;
	clt = serv->clients;
	serv->max = (serv->sock < serv->gfxsock) ? serv->gfxsock : serv->sock;
	while (i++ < *actual)
	{
		save = serv->clients[i].sock;
		if (&serv->clients[i] != (clt + rm))
			serv->max = (save > serv->max) ? save : serv->max;
	}
	if (serv->gfx.sock)
		pdi(serv->gfx.sock, clt + rm);
	printf("%d disconnected\n", (clt + rm)->sock);
	close((clt + rm)->sock);
	memmove(clt + rm, clt + rm + 1, (*actual - rm - 1) * sizeof(t_client));
	(*actual)--;
	serv->connected--;
}

void	client_talking_loop(t_server *serv, int *actu, char *buff)
{
	int			i;

	i = 0;
	while (i < *actu)
	{
		if (FD_ISSET(serv->clients[i].sock, &(serv->rdfs)))
		{
			if (read_client(serv->clients[i].sock, buff) == -1)
				remove_client(serv, i, actu);
			else
				ft_cmd(serv, buff, i);
			break ;
		}
		i++;
	}
}

void	client_talking(t_server *serv, int *actu, char *buff)
{
	int			i;

	i = 0;
	client_talking_loop(serv, actu, buff);
	if (serv->gfx.sock && FD_ISSET(serv->gfx.sock, &(serv->rdfs)))
	{
		if (read_client(serv->gfx.sock, buff) == -1)
		{
			printf("%d disconnected\n", serv->gfx.sock);
			close(serv->gfx.sock);
			serv->gfx.sock = 0;
			serv->max = (serv->sock < serv->gfxsock) ?
				serv->gfxsock : serv->sock;
			i = -1;
			while (i++ < *actu)
				serv->max = (serv->clients[i].sock > serv->max) ?
			serv->clients[i].sock : serv->max;
		}
		else
		{
			cmd_gfx(serv, buff);
			printf("%s\n", buff);
		}
	}
}
