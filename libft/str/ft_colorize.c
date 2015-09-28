/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colorize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 13:51:09 by rbenjami          #+#    #+#             */
/*   Updated: 2014/05/14 17:25:33 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_colorize(t_color color, int backgroud)
{
	static const char	*c[] =

	{
	ANSI_COLOR_RESET,
	ANSI_COLOR_BLACK,
	ANSI_COLOR_RED,
	ANSI_COLOR_GREEN,
	ANSI_COLOR_YELLOW,
	ANSI_COLOR_BLUE,
	ANSI_COLOR_MAGENTA,
	ANSI_COLOR_CYAN,
	ANSI_COLOR_WHITE,
	ANSI_BACKGROUND_COLOR_BLACK,
	ANSI_BACKGROUND_COLOR_RED,
	ANSI_BACKGROUND_COLOR_GREEN,
	ANSI_BACKGROUND_COLOR_YELLOW,
	ANSI_BACKGROUND_COLOR_BLUE,
	ANSI_BACKGROUND_COLOR_MAGENTA,
	ANSI_BACKGROUND_COLOR_CYAN,
	ANSI_BACKGROUND_COLOR_WITHE
	};
	backgroud = (backgroud > 0) ? 8 : 0;
	ft_putstr((char *)c[(int)color + backgroud]);
}
