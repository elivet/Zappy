/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpytab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcin <mgarcin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/30 17:20:00 by rbenjami          #+#    #+#             */
/*   Updated: 2014/06/25 15:56:21 by mgarcin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_cpytab(char **tab, int lenth)
{
	char	**new_tab;
	int		i;
	int		tablen;

	i = 0;
	tablen = ft_tabsize((void **)tab);
	new_tab = (char **)ft_memalloc(sizeof(char *) * lenth + 1);
	while (i < tablen)
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	return (new_tab);
}

int		**ft_cpytab_int(int **tab, int x, int y)
{
	int		**new_tab;
	int		i;
	int		j;
	int		tablen;

	i = 0;
	tablen = ft_tabsize((void **)tab);
	new_tab = (int **)ft_memalloc(sizeof(int *) * x);
	while (i < x)
	{
		j = 0;
		new_tab[i] = ft_memalloc(sizeof(int) * y);
		while (j < y)
		{
			new_tab[i][j] = tab[i][j];
			j++;
		}
		i++;
	}
	return (new_tab);
}
