/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_mandelbrot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:34:17 by tpeters           #+#    #+#             */
/*   Updated: 2022/05/13 03:23:49 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	check_trivial(double x, double y)
{
	double	q;

	if (x * x + 2 * x + 1 + y * y < 0.0625)
		return (1);
	q = (x - 0.25) * (x - 0.25) + y * y;
	if (q * (q + (x - 0.25)) < y * y * 0.25)
		return (1);
	return (0);
}

//https://theses.liacs.nl/pdf/2018-2019-JonckheereLSde.pdf
//http://www.nongnu.org/hpalib/
int	mandel(double x, double y)
{
	double	xn;
	double	yn;
	int		depth;
	double	tmp;

	if (check_trivial(x, y))
		return (DEPTH_MAX);
	xn = 0;
	yn = 0;
	depth = 0;
	while ((xn * xn + yn * yn <= 4) && depth <= DEPTH_MAX)
	{
		tmp = xn * xn - yn * yn + x;
		yn = 2 * xn * yn + y;
		xn = tmp;
		depth++;
	}
	return (depth);
}

void	put_mand_pixels(t_vars *vars, int x, int y, int i)
{
	double	tmp;

	if (vars->mand_depths[x][y] < DEPTH_MAX)
	{
		tmp = (((double)vars->mand_depths[x][y]) / (128)) * 2 * M_PI + i / 5.0;
		put_pixel(&vars->img, x, y, new_color(0, (sin(tmp) + 1) * 255 / 2, (sin(tmp + 2) + 1) * 255 / 2, (sin(tmp + 4) + 1) * 255 / 2, vars->img.endian));
	}
	else
		put_pixel(&vars->img, x, y, new_color(0, 0, 0, 0, vars->img.endian));
}

void	init_depth_array(int in[WIDTH][HEIGHT])
{
	int	c;
	int	d;

	c = 0;
	while (c < WIDTH)
	{
		d = 0;
		while (d < HEIGHT)
		{
			in[c][d] = -1;
			d++;
		}
		c++;
	}
}

void	cp_depth_array(int in[WIDTH][HEIGHT], int out[WIDTH][HEIGHT])
{
	int	c;
	int	d;

	c = 0;
	while (c < WIDTH)
	{
		d = 0;
		while (d < HEIGHT)
		{
			out[c][d] = in[c][d];
			d++;
		}
		c++;
	}
}

void	move_array(t_vars *vars, int hor, int ver)
{
	int	tmp[WIDTH][HEIGHT];
	int	c;
	int	d;

	init_depth_array(tmp);
	c = 0;
	while (c < WIDTH)
	{
		d = 0;
		while (d < HEIGHT)
		{
			if (hor && c + hor >= 0 && c + hor < WIDTH)
				tmp[c + hor][d] = vars->mand_depths[c][d];
			if (ver && d + ver >= 0 && d + ver < HEIGHT)
				tmp[c][d + ver] = vars->mand_depths[c][d];
			d++;
		}
		c++;
	}
	cp_depth_array(tmp, vars->mand_depths);
}
