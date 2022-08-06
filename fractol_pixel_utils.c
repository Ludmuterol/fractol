/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_pixel_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:01:47 by tpeters           #+#    #+#             */
/*   Updated: 2022/08/06 21:51:15 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	coord_to_offset(int x, int y, int line_length, int bits_per_pixel)
{
	return (y * line_length + x * (bits_per_pixel / 8));
}

void	put_pixels(t_vars *vars, int x, int y, int i)
{
	if (vars->depths[x][y] < vars->max_depth)
	{
		if (vars->depths[x][y] >= 0)
		{
			put_pixel(&vars->img, x, y,
				depth_to_col(vars, (double)vars->depths[x][y], i));
		}
		else
		{
			put_pixel(&vars->img, x, y,
				new_color(0, 0, 0, vars->img.endi));
		}
	}
	else
		put_pixel(&vars->img, x, y, new_color(0, 0, 0, vars->img.endi));
}

static void	bf_pixl(struct s_for_each_pixel *s, int *dep, double xt, double yt)
{
	struct s_fract_arguments	fs;

	if (*dep < 0)
	{
		fs.depth_max = s->vars->max_depth;
		fs.x = xt;
		fs.y = yt;
		fs.xn = s->vars->xn;
		fs.yn = s->vars->yn;
		if (s->f == mandel)
		{
			fs.xn = 0;
			fs.yn = 0;
		}
		*dep = s->f(&fs);
	}
}

static int	bf_and_put_all_pixels(struct s_for_each_pixel *stuff, int i)
{
	int							x;
	int							y;
	double						xtrans;
	double						ytrans;

	xtrans = stuff->vars->xmin;
	ytrans = stuff->vars->ymax;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		ytrans = stuff->vars->ymax;
		while (y < HEIGHT)
		{
			bf_pixl(stuff, &(stuff->vars->depths[x][y]), xtrans, ytrans);
			put_pixels(stuff->vars, x, y, i);
			ytrans -= stuff->vars->y_len / HEIGHT;
			y++;
		}
		xtrans += stuff->vars->x_len / WIDTH;
		x++;
	}
	return (mlx_put_image_to_window(stuff->vars->mlx, stuff->vars->win,
			stuff->vars->img.img, 0, 0));
}

int	for_each_pixel(struct s_for_each_pixel *stuff)
{
	static int			i;
	struct s_rect_args	s_args;

	i++;
	s_args.stuff = stuff;
	s_args.x1 = 0;
	s_args.y1 = 0;
	s_args.x2 = WIDTH - 1;
	s_args.y2 = HEIGHT - 1;
	rec_box(&s_args);
	return (bf_and_put_all_pixels(stuff, i));
}
