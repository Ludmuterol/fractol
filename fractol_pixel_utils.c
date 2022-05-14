/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_pixel_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:01:47 by tpeters           #+#    #+#             */
/*   Updated: 2022/05/14 00:46:24 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	coord_to_offset(int x, int y, int line_length, int bits_per_pixel)
{
	return (y * line_length + x * (bits_per_pixel / 8));
}

void	put_pixels(t_vars *vars, int x, int y, int i)
{
	double	tmp;

	if (vars->depths[x][y] < DEPTH_MAX)
	{
		tmp = (((double)vars->depths[x][y]) / (128)) * 2 * M_PI + i / 5.0;
		put_pixel(&vars->img, x, y, new_color(0, (sin(tmp) + 1) * 255 / 2, (sin(tmp + 2) + 1) * 255 / 2, (sin(tmp + 4) + 1) * 255 / 2, vars->img.endian));
	}
	else
		put_pixel(&vars->img, x, y, new_color(0, 0, 0, 0, vars->img.endian));
}

int	for_each_pixel(struct s_for_each_pixel *stuff)
{
	int	x;
	int	y;

	static int i;
	i++;
	
	double xtrans = stuff->vars->xmin;
	double ytrans = stuff->vars->ymax;
	double xstep = stuff->vars->x_len / WIDTH;
	double ystep = stuff->vars->y_len / HEIGHT;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		ytrans = stuff->vars->ymax;
		while (y < HEIGHT)
		{
			if (stuff->vars->depths[x][y] == -1)
				stuff->vars->depths[x][y] = stuff->f(xtrans, ytrans, stuff->vars->xn, stuff->vars->yn);
			put_pixels(stuff->vars, x, y, i);
			ytrans -= ystep;
			y++;
		}
		xtrans += xstep;
		x++;
	}
	return (mlx_put_image_to_window(stuff->vars->mlx, stuff->vars->win, stuff->vars->img.img, 0, 0));
}
