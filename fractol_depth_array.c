/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_depth_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:08:41 by tpeters           #+#    #+#             */
/*   Updated: 2022/05/14 00:10:25 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

static void	cp_depth_array(int in[WIDTH][HEIGHT], int out[WIDTH][HEIGHT])
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
				tmp[c + hor][d] = vars->depths[c][d];
			if (ver && d + ver >= 0 && d + ver < HEIGHT)
				tmp[c][d + ver] = vars->depths[c][d];
			d++;
		}
		c++;
	}
	cp_depth_array(tmp, vars->depths);
}
