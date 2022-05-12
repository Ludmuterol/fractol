/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_pixel_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:01:47 by tpeters           #+#    #+#             */
/*   Updated: 2022/05/12 13:36:19 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	coord_to_offset(int x, int y, int line_length, int bits_per_pixel)
{
	return (y * line_length + x * (bits_per_pixel / 8));
}

int	for_each_pixel(struct s_for_each_pixel_params *input)
{
	int	x;
	int	y;

	static int i;
	i++;
	
	double xtrans = input->vars->xmin;
	double ytrans = input->vars->ymax;
	double xstep = input->vars->x_len / WIDTH;
	double ystep = input->vars->y_len / HEIGHT;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		ytrans = input->vars->ymax;
		while (y < HEIGHT)
		{
			(input->func)(input->vars, x, y, xtrans, ytrans, i);
			ytrans -= ystep;
			y++;
		}
		xtrans += xstep;
		x++;
	}

	return (mlx_put_image_to_window(input->vars->mlx, input->vars->win, input->vars->img.img, 0, 0));
}
