/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_mandelbrot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:34:17 by tpeters           #+#    #+#             */
/*   Updated: 2022/05/12 21:42:54 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//https://theses.liacs.nl/pdf/2018-2019-JonckheereLSde.pdf

int	mandel(double x, double y)
{
	double	xn = 0; 
	double	yn = 0;
	int		depth = 0;
	if (x * x + 2 * x + 1 + y * y < 0.0625)
		return (DEPTH_MAX);
	double q = (x - 0.25) * (x - 0.25) + y * y;
	if (q * (q + (x - 0.25)) < y * y * 0.25)
		return (DEPTH_MAX);
	while (depth <= DEPTH_MAX)
	{
		double xx = xn * xn;
		double yy = yn * yn;
		double tmp = xx - yy + x; 
		yn = 2 * xn * yn + y;
		xn = tmp;
		depth++;
		if (xx + yy > 4)
			return (depth);
	}
	return (depth);
}

void	put_mand_pixels(t_vars *vars, int x, int y, int i)
{
	if (vars->mand_depths[x][y] < DEPTH_MAX)
	{
		double tmp = (((double)vars->mand_depths[x][y]) / (128)) * 2 * M_PI + i / 5.0;
		put_pixel(&vars->img, x, y, new_color(0, (sin(tmp) + 1) * 255/2, (sin(tmp + 2) + 1) * 255/2, (sin(tmp + 4) + 1) * 255/2, vars->img.endian));
	}
	else
		put_pixel(&vars->img, x, y, new_color(0, 0, 0, 0, vars->img.endian));
}

void	move_array(t_vars *vars, int hor, int ver)
{
	int	tmp[WIDTH][HEIGHT];
	int c, d;
	
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
	c = 0;
	while (c < WIDTH)
	{
		d = 0;
		while (d < HEIGHT)
		{
			vars->mand_depths[c][d] = tmp[c][d];
			d++;
		}
		c++;
	}
}

void	init_depth_array(int in[WIDTH][HEIGHT])
{
	int c, d;
	
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
