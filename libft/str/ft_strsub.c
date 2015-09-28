/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/17 11:25:17 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/17 14:28:51 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, size_t start, size_t len)
{
	size_t			i;
	char			*str;

	i = 0;
	str = ft_strnew(len);
	if (!str || !s)
		return (0);
	while (i++ < len)
		str[i - 1] = s[start++];
	return (str);
}
