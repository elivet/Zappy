/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/27 11:26:39 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/27 11:26:50 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freetab(void **tab)
{
	int		i;

	i = ft_tabsize(tab);
	if (tab)
	{
		while (i >= 0)
		{
			free(*tab);
			*tab = NULL;
			tab++;
			i--;
		}
		tab = NULL;
	}
}
