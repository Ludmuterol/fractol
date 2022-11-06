/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bounds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:24:17 by tpeters           #+#    #+#             */
/*   Updated: 2022/11/06 22:31:52 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_bounds(t_vars *vars, t_bounds in)
{
	vars->xmin = in.a;
	vars->xmax = in.b;
	vars->ymin = in.c;
	vars->ymax = in.d;
	calc_len(vars);
}

void	calc_len(t_vars *vars)
{
	vars->x_len = (vars->xmax - vars->xmin);
	vars->y_len = (vars->ymax - vars->ymin);
}

void	inc_max_dep(t_vars *vars)
{
	int	c;
	int	d;

	c = 0;
	if (vars->show_rects)
		init_depth_array(vars->depths);
	else
	{
		while (c < WIDTH)
		{
			d = 0;
			while (d < HEIGHT)
			{
				if (vars->depths[c][d] == vars->max_depth)
					vars->depths[c][d] = -1;
				d++;
			}
			c++;
		}
	}
	if (vars->max_depth < 50)
		vars->max_depth += 5 - 4 * (vars->max_depth < 10);
	else
		vars->max_depth += 10;
}

void	dec_max_dep(t_vars *vars)
{
	if (vars->max_depth > 0)
	{
		if (vars->max_depth <= 10)
			vars->max_depth -= 1;
		else if (vars->max_depth <= 50)
			vars->max_depth -= 5;
		else
			vars->max_depth -= 10;
	}
}
