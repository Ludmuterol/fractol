/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_pixel_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:01:47 by tpeters           #+#    #+#             */
/*   Updated: 2022/05/12 13:54:00 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	coord_to_offset(int x, int y, int line_length, int bits_per_pixel)
{
	return (y * line_length + x * (bits_per_pixel / 8));
}

int	for_each_pixel(t_vars *vars)
{
	int	x;
	int	y;

	static int i;
	i++;
	
	double xtrans = vars->xmin;
	double ytrans = vars->ymax;
	double xstep = vars->x_len / WIDTH;
	double ystep = vars->y_len / HEIGHT;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		ytrans = vars->ymax;
		while (y < HEIGHT)
		{
			if (vars->recalc)
				vars->mand_depths[x][y] = mandel(xtrans, ytrans);
			testfunc(vars, x, y, i);
			ytrans -= ystep;
			y++;
		}
		xtrans += xstep;
		x++;
	}
	vars->recalc = 0;
	return (mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0));
}
