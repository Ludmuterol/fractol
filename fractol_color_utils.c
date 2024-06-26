/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_color_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:57:41 by tpeters           #+#    #+#             */
/*   Updated: 2022/08/06 22:12:11 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color	new_color(unsigned char r, unsigned char g, unsigned char b, int endian)
{
	t_color	ret;

	if (!endian)
	{
		ret.t = (unsigned char) b;
		ret.r = (unsigned char) g;
		ret.g = (unsigned char) r;
		ret.b = (unsigned char) 0;
		return (ret);
	}
	ret.t = (unsigned char) 0;
	ret.r = (unsigned char) r;
	ret.g = (unsigned char) g;
	ret.b = (unsigned char) b;
	return (ret);
}

void	put_pixel(t_data *img, int x, int y, t_color color)
{
	char	*dst;

	dst = img->addr + coord_to_offset(x, y, img->ll, img->bpp);
	*(unsigned int *)dst = color.color;
}

void	fill_rec(struct s_rect_args *s, int value)
{
	int	x;
	int	y;

	x = s->x1;
	while (x <= s->x2)
	{
		y = s->y1;
		while (y <= s->y2)
		{
			if (s->stuff->vars->depths[x][y] == -1)
			{
				s->stuff->vars->depths[x][y] = value;
			}
			y++;
		}
		x++;
	}
}

t_color	depth_to_col(t_vars *vars, double dep, int i)
{
	double	tmp;

	if (vars->is_newton)
	{
		if (dep == 0)
			return (new_color(0, 0, 0, vars->img.endi));
		if (dep == 1)
			return (new_color(255, 0, 0, vars->img.endi));
		if (dep == 2)
			return (new_color(0, 255, 0, vars->img.endi));
		if (dep == 3)
			return (new_color(0, 0, 255, vars->img.endi));
		else
			return (new_color(255, 255, 0, vars->img.endi));
	}
	if (vars->max_depth >= 80)
		tmp = ((dep) / 80) * 2 * M_PI + i / 25.0;
	else
		tmp = ((dep) / vars->max_depth) * 2 * M_PI + i / 25.0;
	return (new_color((sin(tmp) + 1) * 255 / 2,
			(sin(tmp + 2) + 1) * 255 / 2,
			(sin(tmp + 4) + 1) * 255 / 2, vars->img.endi));
}
