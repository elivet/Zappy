/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_case.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 14:39:22 by jflorimo          #+#    #+#             */
/*   Updated: 2014/06/26 14:39:22 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"
#include "libft.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

static char	*g_tab[7] =
{
	"nourriture ",
	"linemate ",
	"deraumere ",
	"sibur ",
	"mendiane ",
	"phiras ",
	"thystame "
};

int			count_player(t_server *serv, int actual, int x, int y)
{
	int		i;
	int		nb_player;

	i = 0;
	nb_player = 0;
	while (i < serv->connected)
	{
		if (i != actual && serv->clients[i].x == x && serv->clients[i].y == y)
			nb_player++;
		i++;
	}
	return (nb_player);
}

void		ft_case(t_server *serv, char **result, enum e_res r, t_case t)
{
	char	*tmp;
	int		x;
	int		y;

	x = t.x;
	y = t.y;
	if (*result)
	{
		tmp = ft_trunc("%s%p", *result, pattern(serv->map.map[y][x].res[r],
			g_tab[r]));
		free(*result);
		*result = tmp;
	}
	else
		*result = ft_trunc("%p", pattern(serv->map.map[y][x].res[r],
			g_tab[r]));
}

t_case		init_tcase(t_server *serv, int v, int h)
{
	t_case	t;

	t.y = (v >= serv->map.y) ? (v % serv->map.y) : v;
	t.y = (t.y < 0) ? (serv->map.y + t.y) : t.y;
	t.x = (h >= serv->map.x) ? (h % serv->map.x) : h;
	t.x = (t.x < 0) ? (serv->map.x + t.x) : t.x;
	return (t);
}

void		set_ftcase(t_server *serv, t_case t, char **result)
{
	ft_case(serv, result, LINEMATE, t);
	ft_case(serv, result, DERAUMERE, t);
	ft_case(serv, result, SIBUR, t);
	ft_case(serv, result, MENDIANE, t);
	ft_case(serv, result, PHIRAS, t);
	ft_case(serv, result, THYSTAME, t);
}

char		*obtain_case(t_server *serv, int v, int h, int actual)
{
	t_case	t;
	char	*result;
	int		indic;
	char	*tmp;

	indic = 0;
	t = init_tcase(serv, v, h);
	if (serv->map.map[t.y][t.x].nbr <= 0)
		return (NULL);
	result = ft_trunc("%p", pattern(serv->map.map[t.y][t.x].res[NOURRITURE],
		"nourriture "));
	set_ftcase(serv, t, &result);
	if (result)
	{
		tmp = ft_trunc("%s%p", result,
			pattern(count_player(serv, actual, t.x, t.y), "joueur "));
		free(result);
		result = tmp;
	}
	else
		result = ft_trunc("%p", pattern(count_player(serv, actual, t.x, t.y),
		"joueur "));
	if (result)
		result[ft_strlen(result) - 1] = 0;
	return (result);
}
