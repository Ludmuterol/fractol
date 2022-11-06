/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:20:16 by tpeters           #+#    #+#             */
/*   Updated: 2022/11/06 22:24:33 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_move(int x, int y, t_vars *vars)
{
	if (vars->get_mouse_move)
	{
		vars->xn = vars->xmin + (((double)x / WIDTH) * vars->x_len);
		vars->yn = vars->ymax - (((double)y / HEIGHT) * vars->y_len);
		init_depth_array(vars->depths);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	double		x_dist;
	double		y_dist;
	t_bounds	b;

	if (button == SCRL_UP || button == SCRL_DWN)
	{
		if (button == SCRL_UP)
		{
			x_dist = (vars->x_len * ZOOM) / 2;
			y_dist = (vars->y_len * ZOOM) / 2;
		}
		else
		{
			x_dist = (vars->x_len / ZOOM) / 2;
			y_dist = (vars->y_len / ZOOM) / 2;
		}
		b.a = vars->xmin + (((double)x / WIDTH) * vars->x_len) - x_dist;
		b.b = vars->xmin + (((double)x / WIDTH) * vars->x_len) + x_dist;
		b.c = vars->ymax - (((double)y / HEIGHT) * vars->y_len) - y_dist;
		b.d = vars->ymax - (((double)y / HEIGHT) * vars->y_len) + y_dist;
		set_bounds(vars, b);
		init_depth_array(vars->depths);
	}
	return (0);
}
