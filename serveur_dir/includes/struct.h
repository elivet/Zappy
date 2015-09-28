/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 22:43:37 by jflorimo          #+#    #+#             */
/*   Updated: 2014/06/26 22:43:38 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# define MAX_CLIENTS			(1000)

enum							e_res
{
	NOURRITURE,
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME
};

typedef struct s_cmd			t_cmd;
typedef struct sockaddr_in		t_sockaddr_in;
typedef struct sockaddr			t_sockaddr;
typedef struct in_addr			t_in_addr;

typedef struct					s_square
{
	int							nbr;
	enum e_res					res[7];
}								t_square;

typedef struct					s_inventaire
{
	int							nbr;
	enum e_res					res[7];
}								t_inventaire;

typedef struct					s_queue
{
	char						*arg;
	t_cmd						*cmd;
	double						exe_time;
}								t_queue;

typedef struct					s_client
{
	int							sock;
	int							x;
	int							y;
	int							dir;
	char						*team;
	int							lvl;
	double						last_cmd_end;
	double						time;
	t_queue						queue[10];
	t_inventaire				inventaire;
}								t_client;

typedef struct					s_map
{
	int							x;
	int							y;
	t_square					**map;
}								t_map;

typedef struct					s_gfx
{
	int							sock;
}								t_gfx;

typedef struct					s_teams
{
	char						*name;
	int							eggs;
	int							baby;
	int							egg_x[MAX_CLIENTS];
	int							egg_y[MAX_CLIENTS];
	double						time[MAX_CLIENTS];
	int							id[MAX_CLIENTS];
}								t_team;

typedef struct					s_server
{
	int							sock;
	int							gfxsock;
	int							port;
	t_map						map;
	int							max_clients;
	int							connected;
	int							t;
	char						**team;
	int							argc;
	t_team						teams[MAX_CLIENTS];
	int							max;
	int							max_food;
	int							num_egg;
	fd_set						rdfs;
	t_client					clients[MAX_CLIENTS];
	t_gfx						gfx;
}								t_server;

struct							s_cmd
{
	char						*cmd;
	void						(*f)(t_server *, int, char *);
	int							time;
};

typedef struct					s_case
{
	int							y;
	int							x;
}								t_case;

typedef struct					s_voir
{
	int							h;
	int							v;
	int							i;
	int							tmp;
	int							tmp2;
	char						*result;
	char						*tmp_result;
	char						*tmp2_result;
}								t_voir;

#endif
