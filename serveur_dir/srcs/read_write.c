/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elivet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 20:48:50 by elivet            #+#    #+#             */
/*   Updated: 2014/06/26 20:48:52 by elivet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <libft.h>
#include "../includes/serveur.h"

int		read_client(int sock, char *buff)
{
	int		r;

	r = 0;
	if ((r = recv(sock, buff, BUF_SIZE, 0)) < 0)
	{
		error("recv");
		r = 0;
	}
	buff[r - 1] = 0;
	return (r - 1);
}

void	write_client(int sock, const char *buff)
{
	char	*tmp;

	tmp = ft_trunc("%s\n", buff);
	if (send(sock, tmp, ft_strlen((char *)tmp), 0) < 0)
	{
		free(tmp);
		exit_error("send");
	}
	free(tmp);
}
