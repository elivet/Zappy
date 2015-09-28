/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 15:27:56 by jflorimo          #+#    #+#             */
/*   Updated: 2014/06/26 15:27:56 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

int			cmd_fork_loop(t_server *serv, int actual)
{
	int		i;
	int		sv;
	int		sv2;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (!ft_strcmp(serv->clients[actual].team, serv->teams[i].name))
		{
			sv = serv->teams[i].eggs;
			serv->teams[i].egg_x[sv] = serv->clients[actual].x;
			serv->teams[i].egg_y[sv] = serv->clients[actual].y;
			serv->teams[i].id[sv] = serv->num_egg;
			serv->teams[i].eggs++;
			serv->num_egg++;
			serv->teams[i].egg_y[serv->teams[i].eggs] = serv->num_egg;
			sv = serv->t;
			sv2 = CLOCKS_PER_SEC;
			serv->teams[i].time[i] = ((double)clock() / sv2) + (600 / sv);
			break ;
		}
		i++;
	}
	return (i);
}

void		cmd_fork(t_server *serv, int actual, char *buff)
{
	int		i;

	(void)buff;
	i = cmd_fork_loop(serv, actual);
	if (serv->gfx.sock)
		enw(serv->gfx.sock, &serv->teams[i], serv->teams[i].eggs - 1,
	serv->clients[actual].sock);
	write_client(serv->clients[actual].sock, "ok");
}

int			ft_wait_loop(t_server *serv, t_cmd *cmd, int actual, char *buff)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (serv->clients[actual].queue[i].cmd == NULL)
		{
			serv->clients[actual].queue[i].arg = ft_strdup(buff);
			serv->clients[actual].queue[i].cmd = cmd;
			serv->clients[actual].queue[i].exe_time =
			serv->clients[actual].last_cmd_end;
			break ;
		}
		i++;
	}
	return (i);
}

void		ft_wait(t_server *serv, t_cmd *cmd, int actual, char *buff)
{
	double					time;
	double					delta;
	int						i;

	time = (double)((double)clock() / (double)CLOCKS_PER_SEC);
	delta = (double)0;
	if (serv->clients[actual].last_cmd_end > time)
		delta = serv->clients[actual].last_cmd_end - (double)time;
	delta = (double)((double)cmd->time / (double)serv->t) + (double)delta;
	serv->clients[actual].last_cmd_end = (double)time + delta;
	if (!ft_strncmp("incantation", buff, 11))
		cmd_pre_incantation(serv, actual, buff);
	i = ft_wait_loop(serv, cmd, actual, buff);
	if (i == 10)
		write_client(serv->clients[actual].sock, "ko");
}
