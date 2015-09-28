/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_gfx3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharpen <lcharpen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 14:17:57 by lcharpen          #+#    #+#             */
/*   Updated: 2014/06/26 14:17:59 by lcharpen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "serveur.h"

void		enw(int csock, t_team *team, int j, int owner)
{
	char	*msg;

	msg = ft_trunc("enw #%d #%d %d %d", \
					team->id[j], \
					owner, \
					team->egg_x[j], \
					team->egg_y[j]);
	write_client(csock, msg);
	free(msg);
}

void		seg(int csock, char *winning_team)
{
	char	*msg;

	msg = ft_trunc("seg %d", winning_team);
	write_client(csock, msg);
	free(msg);
}

void		smg(int csock, char *buff)
{
	char	*msg;

	msg = ft_trunc("smg %s", buff);
	write_client(csock, msg);
	free(msg);
}

void		suc(int csock)
{
	write_client(csock, "suc");
}

void		sbp(int csock)
{
	write_client(csock, "sbp");
}
