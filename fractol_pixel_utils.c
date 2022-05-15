/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_pixel_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:01:47 by tpeters           #+#    #+#             */
/*   Updated: 2022/05/15 04:00:02 by tpeters          ###   ########.fr       */
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
		if (vars->depths[x][y] >= 0)
		{
			tmp = (((double)vars->depths[x][y]) / (128)) * 2 * M_PI + i / 5.0;
			put_pixel(&vars->img, x, y, new_color(0, (sin(tmp) + 1) * 255 / 2, (sin(tmp + 2) + 1) * 255 / 2, (sin(tmp + 4) + 1) * 255 / 2, vars->img.endian));
		}
		else
		{
			put_pixel(&vars->img, x, y, new_color(0, 255, 0, 0, vars->img.endian));
		}
	}
	else
		put_pixel(&vars->img, x, y, new_color(0, 0, 0, 0, vars->img.endian));
}

int	O_for_each_pixel(struct s_for_each_pixel *stuff)
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

int	fill_rec_bord(struct s_for_each_pixel *stuff, int x1, int y1, int x2, int y2)
{
	int	check = -1;
	int ret = 1;
	int	tmp = x1;
	while (tmp <= x2)
	{
		if (stuff->vars->depths[tmp][y1] == -1)
		{
			double xtrans = stuff->vars->xmin + ((double)tmp / WIDTH) * stuff->vars->x_len;
			double ytrans = stuff->vars->ymax - ((double)y1 / HEIGHT) * stuff->vars->y_len;
			stuff->vars->depths[tmp][y1] = stuff->f(xtrans, ytrans, stuff->vars->xn, stuff->vars->yn);
		}
		if (ret && check != stuff->vars->depths[tmp][y1])
		{
			if (check == -1)
				check = stuff->vars->depths[tmp][y1];
			else
				ret = 0;
		}
		if (stuff->vars->depths[tmp][y2] == -1)
		{
			double xtrans = stuff->vars->xmin + ((double)tmp / WIDTH) * stuff->vars->x_len;
			double ytrans = stuff->vars->ymax - ((double)y2 / HEIGHT) * stuff->vars->y_len;
			stuff->vars->depths[tmp][y2] = stuff->f(xtrans, ytrans, stuff->vars->xn, stuff->vars->yn);
		}
		if (ret && check != stuff->vars->depths[tmp][y2])
		{
			if (check == -1)
				check = stuff->vars->depths[tmp][y2];
			else
				ret = 0;
		}
		tmp++;
	}
	tmp = y1;
	while (tmp <= y2)
	{
		if (stuff->vars->depths[x1][tmp] == -1)
		{
			double xtrans = stuff->vars->xmin + ((double)x1 / WIDTH) * stuff->vars->x_len;
			double ytrans = stuff->vars->ymax - ((double)tmp / HEIGHT) * stuff->vars->y_len;
			stuff->vars->depths[x1][tmp] = stuff->f(xtrans, ytrans, stuff->vars->xn, stuff->vars->yn);
		}
		if (ret && check != stuff->vars->depths[x1][tmp])
		{
			if (check == -1)
				check = stuff->vars->depths[x1][tmp];
			else
				ret = 0;
		}
		if (stuff->vars->depths[x2][tmp] == -1)
		{
			double xtrans = stuff->vars->xmin + ((double)x2 / WIDTH) * stuff->vars->x_len;
			double ytrans = stuff->vars->ymax - ((double)tmp / HEIGHT) * stuff->vars->y_len;
			stuff->vars->depths[x2][tmp] = stuff->f(xtrans, ytrans, stuff->vars->xn, stuff->vars->yn);
		}
		if (ret && check != stuff->vars->depths[x2][tmp])
		{
			if (check == -1)
				check = stuff->vars->depths[x2][tmp];
			else
				ret = 0;
		}
		tmp++;
	}
	if (check == DEPTH_MAX)
		return (ret);
	return (0);
}

void	fill_rec_black(struct s_for_each_pixel *stuff, int x1, int y1, int x2, int y2)
{
	int	x, y;

	x = x1;
	while (x <= x2)
	{
		y = y1;
		while (y <= y2)
		{
			if (stuff->vars->depths[x][y] == -1)
			{
				stuff->vars->depths[x][y] = -2;
			}
			y++;
		}
		x++;
	}
}

void	rec_box(struct s_for_each_pixel *stuff, int x1, int y1, int x2, int y2)
{
	if (fill_rec_bord(stuff, x1, y1, x2, y2))
		fill_rec_black(stuff, x1, y1, x2, y2);
	else
	{
		if (x2 - x1 < 6 || y2 - y1 < 6)
			return ;
		rec_box(stuff, x1, y1, x1 + (x2 - x1) / 2, y1 + (y2 - y1) / 2);
		rec_box(stuff, x1 + (x2 - x1) / 2, y1, x2, y1 + (y2 - y1) / 2);
		rec_box(stuff, x1, y1 + (y2 - y1) / 2, x1 + (x2 - x1) / 2, y2);
		rec_box(stuff, x1 + (x2 - x1) / 2, y1 + (y2 - y1) / 2, x2, y2);
	}
}

int	for_each_pixel(struct s_for_each_pixel *stuff)
{
	rec_box(stuff, 0, 0, WIDTH - 1, HEIGHT - 1);
	return (O_for_each_pixel(stuff));
}