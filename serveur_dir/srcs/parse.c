/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elivet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 20:48:27 by elivet            #+#    #+#             */
/*   Updated: 2014/06/26 20:48:30 by elivet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include "../includes/serveur.h"
#include <time.h>

static void		stock_param_team(t_server *serv, char **argv, int *i, int *j)
{
	int			k;

	(*i)++;
	while (*i < serv->argc && argv[*i + *j] && argv[*i + *j][0] != '-')
		(*j)++;
	serv->team = ft_memalloc(sizeof(char **) * (*j + 1));
	k = 0;
	while (k < *j)
	{
		serv->team[k] = argv[*i + k];
		k++;
	}
	*i += k - 1;
}

static int		stock_param(int *stock, char **argv, int *i)
{
	if (*stock == 0)
		*stock = ft_atoi(argv[++(*i)]);
	else
		return (-1);
	return (0);
}

static int		second_parse_flag(t_server *serv, char **argv, int *i, int *j)
{
	if (argv[*i][1] == 'c')
	{
		if (stock_param(&(serv->max_clients), argv, i) == -1)
			return (-1);
	}
	else if (argv[*i][1] == 't')
	{
		if (stock_param(&(serv->t), argv, i) == -1)
			return (-1);
	}
	else if (argv[*i][1] == 'n')
		stock_param_team(serv, argv, i, j);
	return (0);
}

static int		parse_flag(t_server *serv, char **argv, int *i, int *j)
{
	if (argv[*i][1] == 'p')
	{
		if (stock_param(&(serv->port), argv, i) == -1)
			return (-1);
	}
	else if (argv[*i][1] == 'x')
	{
		if (stock_param(&(serv->map.x), argv, i) == -1)
			return (-1);
	}
	else if (argv[*i][1] == 'y')
	{
		if (stock_param(&(serv->map.y), argv, i) == -1)
			return (-1);
	}
	else if (argv[*i][1] == 'c' || argv[*i][1] == 't' || argv[*i][1] == 'n')
	{
		if (second_parse_flag(serv, argv, i, j) == -1)
			return (-1);
	}
	else
		return (-1);
	return (0);
}

int				parse_param(char *argv[], t_server *serv)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (i < serv->argc)
	{
		if (argv[i][0] == '-' && ft_strlen(argv[i]) == 2 && i + 1 < serv->argc)
		{
			if (parse_flag(serv, argv, &i, &j) == -1)
				return (-1);
		}
		else
			return (-1);
		i++;
	}
	if (!check_args(serv) || j == 0)
		return (-1);
	return (0);
}
