/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_c_voir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 14:50:32 by jflorimo          #+#    #+#             */
/*   Updated: 2014/06/26 14:50:33 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

void		voir2(t_voir *t, t_server *serv, int actual)
{
	if (serv->clients[actual].dir % 2)
		t->tmp_result = obtain_case(serv, t->h, t->v, actual);
	else
		t->tmp_result = obtain_case(serv, t->v, t->h, actual);
	t->h = serv->clients[actual].dir < 2 ? t->h + 1 : t->h - 1;
	t->tmp2_result = ft_strdup(t->result);
	free(t->result);
	if (t->tmp_result && ft_strcmp(t->tmp2_result, "{"))
		t->result = ft_trunc("%s, %s", t->tmp2_result, t->tmp_result);
	else if (t->tmp_result)
		t->result = ft_strjoin(t->tmp2_result, t->tmp_result);
	else
	{
		if (!ft_strcmp(t->tmp2_result, "{"))
			t->result = ft_trunc("{ ");
		else
			t->result = ft_trunc("%s, ", t->tmp2_result);
	}
	free(t->tmp2_result);
	if (t->tmp_result)
		free(t->tmp_result);
}

t_voir		init_t(t_server *serv, int actual)
{
	t_voir	t;

	t.i = -1;
	t.tmp = 1;
	t.v = serv->clients[actual].dir % 2 ? serv->clients[actual].x :
		serv->clients[actual].y;
	t.h = serv->clients[actual].dir % 2 ? serv->clients[actual].y :
		serv->clients[actual].x;
	t.result = ft_strdup("{");
	return (t);
}

void		cmd_voir(t_server *serv, int actual, char *buff)
{
	t_voir	t;

	(void)buff;
	t = init_t(serv, actual);
	while (t.i < ((serv->clients[actual].lvl + 1) *
		(serv->clients[actual].lvl + 1) - 1))
	{
		t.tmp2 = t.tmp;
		t.tmp = (t.tmp * t.tmp) - 1;
		t.h = serv->clients[actual].dir < 2 ? t.h - (t.tmp2 - 1) :
			t.h + (t.tmp2 - 1);
		while (t.i < t.tmp)
		{
			t.i++;
			voir2(&t, serv, actual);
		}
		t.h = serv->clients[actual].dir % 2 ? serv->clients[actual].y :
			serv->clients[actual].x;
		t.v = (serv->clients[actual].dir % 3) ? t.v + 1 : t.v - 1;
		t.tmp = t.tmp2 + 1;
	}
	t.tmp_result = ft_strjoin(t.result, "}");
	free(t.result);
	write_client(serv->clients[actual].sock, t.tmp_result);
	free(t.tmp_result);
}
