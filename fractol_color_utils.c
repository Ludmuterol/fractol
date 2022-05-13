/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_color_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:57:41 by tpeters           #+#    #+#             */
/*   Updated: 2022/05/13 03:25:37 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//endian = 0 -> Windows
t_color	new_color(unsigned char t, unsigned char r, unsigned char g, unsigned char b, int endian)
{
	t_color	ret;

	if (!endian)
	{
		ret.t = b;
		ret.r = g;
		ret.g = r;
		ret.b = t;
		return (ret);
	}
	ret.t = t;
	ret.r = r;
	ret.g = g;
	ret.b = b;
	return (ret);
}

void	put_pixel(t_data *img, int x, int y, t_color color)
{
	char	*dst;

	dst = img->addr + coord_to_offset(x, y, img->line_length, img->bits_per_pixel);
	*(unsigned int *)dst = color.color;
}
