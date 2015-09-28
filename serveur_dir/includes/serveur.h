/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 22:43:24 by jflorimo          #+#    #+#             */
/*   Updated: 2014/06/26 22:43:25 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <netdb.h>
# include "struct.h"

# define INVALID_SOCKET			(-1)
# define SOCKET_ERROR			(-1)
# define CRLF					("\r\n")
# define BUF_SIZE				(1024)

/*
**	CLIENT_CTRL
*/
void		clear_clients(t_client *clients, int actual);
int			new_client(t_server *server, int *actual, char *buff);
int			new_gfxclient(t_server *server, char *buff);
void		client_talking(t_server *serv, int *actu, char *buff);
void		remove_client(t_server *serv, int rm, int *actual);

/*
**	READ_WRITE
*/
int			read_client(int sock, char *buff);
void		write_client(int sock, const char *buff);
void		send_message_to_all_clients(t_client *clts, t_client *s, int a,
	char *b);

/*
**	INIT
*/
int			assign_team(t_server *serv, char *team, int actual);
void		create_map(t_server *serv);
void		init_gfx(t_server *serv, int csock);
void		init_client(t_server *serv, int actual);
int			parse_param(char *argv[], t_server *serv);
int			check_args(t_server *serv);
void		init_time(t_server *server, int *actual);
void		init_eggs(t_server *server);
void		init_server(t_server *server, int gfxsock, int sock);
void		init_fds(t_server *server, int actual);
void		server(int sock, int gfxsock, t_server *server);

/*
**	CMD
*/
void		ft_cmd(t_server *serv, char *buff, int actual);
void		cmd_prendre(t_server *serv, int actual, char *buff);
void		connect_nbr(t_server *serv, int actual, char *buff);
void		cmd_poser(t_server *serv, int actual, char *buff);
void		do_cmd(t_server *server);
int			is_egg_connect(t_server *serv, int actual);
int			connect_nbr_init(t_server *serv, int actual, char *buff);
void		cmd_inventaire(t_server *serv, int actual, char *buff);
int			choose_k(t_server *serv, int dest, double x, double y);
int			findcase(t_server *serv, int dest, int src);
void		cmd_broadcast(t_server *serv, int actual, char *buff);
void		cmd_fork(t_server *serv, int actual, char *buff);
void		ft_wait(t_server *serv, t_cmd *cmd, int actual, char *buff);

/*
**	CMD_BROADCAST
*/
void		cmd_broadcast(t_server *serv, int actual, char *buff);

/*
**	CMD_MOVE
*/
void		cmd_avance(t_server *serv, int actual, char *buff);
void		cmd_droite(t_server *serv, int actual, char *buff);
void		cmd_gauche(t_server *serv, int actual, char *buff);

/*
**	CMD_CASE
*/
void		ft_case(t_server *serv, char **result, enum e_res r, t_case t);
char		*obtain_case(t_server *serv, int v, int h, int actual);
int			count_player(t_server *serv, int actual, int x, int y);

/*
**	CMD_C_EXPULSE
*/
void		cmd_expulse(t_server *serv, int actual, char *buff);
void		expulse_item(t_server *serv, int actual, int *nb);
int			find_client_to_expulse(t_server *serv, int actual, int *client);
int			expulser_direction(t_server *serv, int actual, int who);

/*
**	CMD_C_VOIR
*/
void		cmd_voir(t_server *serv, int actual, char *buff);

/*
**	CMD_C_LVL
*/
int			verif_lvl_tb(t_server *serv, int actual);
void		lvl_up_player(t_server *serv, int actual, int x, int y);

/*
**	CMD_C_INCANTATION
*/
void		cmd_incantation(t_server *serv, int actual, char *buff);
void		cmd_pre_incantation(t_server *serv, int actual, char *buff);

/*
**	CMD_GFX
*/
void		cmd_gfx(t_server *serv, char *buff);
void		bct(int csock, t_server *serv, int x, int y);
void		mct(int csock, t_server *serv);
void		tna(int csock, t_server *serv);
void		pnw(int csock, t_client *client);
void		ppo(int csock, t_client *client);
void		pgt(int csock, t_client *client, enum e_res res);
void		pdr(int csock, t_client *client, enum e_res res);
void		pin(int csock, t_client *client);
void		mct(int csock, t_server *serv);
void		pex(int csock, t_client *client);
void		pbc(int csock, char *buff, t_client *client);
void		enw(int csock, t_team *team, int j, int owner);
void		seg(int csock, char *winning_team);
void		smg(int csock, char *buff);
void		suc(int csock);
void		sbp(int csock);
void		plv(int csock, t_client *client);
void		pie(int csock, int x, int y, int r);
void		pfk(int csock, t_client *client);
void		pdi(int csock, t_client *client);
void		eht(int csock, int num_egg);
void		ebo(int csock, int num_egg);
void		edi(int csock, int num_egg);
void		sgt(int csock, time_t *time);
void		pic(int csock, int actual, t_server *serv);
void		msz(int csock, t_map *map);

/*
**	REGEN_FOOD
*/
int			count_food_on_map(t_server *serv);
void		get_food(int y, int x, t_server *serv);
void		regen_food(t_server *serv);
void		regen_food_two(t_server *serv);

#endif
