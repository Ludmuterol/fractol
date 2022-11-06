/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:18:21 by tpeters           #+#    #+#             */
/*   Updated: 2022/11/06 22:32:27 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	arrow_key_press(int kc, t_vars *vars)
{
	double	tmp;

	if (kc == XK_RIGHT || kc == XK_LEFT)
	{
		tmp = (vars->x_len / WIDTH) * MOVE * (1 - (kc == XK_LEFT) * 2);
		vars->xmin += tmp;
		vars->xmax += tmp;
		move_array(vars, -MOVE + 2 * MOVE * (kc == XK_LEFT), 0);
	}
	if (kc == XK_UP || kc == XK_DOWN)
	{
		tmp = (vars->y_len / HEIGHT) * MOVE * (1 - ((kc == XK_DOWN) * 2));
		vars->ymin += tmp;
		vars->ymax += tmp;
		move_array(vars, 0, MOVE - 2 * MOVE * (kc == XK_DOWN));
	}
	calc_len(vars);
}

static void	toggle_rects(t_vars *vars)
{
	vars->show_rects = !vars->show_rects;
	init_depth_array(vars->depths);
}

static int	second_key_press(int kc, struct s_for_each_pixel *s)
{
	if (kc == XK_M)
	{
		s->f = mandel;
		s->vars->is_newton = 0;
		init_depth_array(s->vars->depths);
	}
	if (kc == XK_J)
	{
		s->f = julia;
		s->vars->is_newton = 0;
		init_depth_array(s->vars->depths);
	}
	if (kc == XK_N)
	{
		s->f = newton;
		s->vars->is_newton = 1;
		init_depth_array(s->vars->depths);
	}
	return (0);
}

int	key_press(int kc, struct s_for_each_pixel *s)
{
	if (kc == XK_ESCAPE)
		quit(s->vars);
	if (kc == XK_LEFT || kc == XK_DOWN || kc == XK_UP || kc == XK_RIGHT)
		arrow_key_press(kc, s->vars);
	if (kc == XK_P)
		s->vars->get_mouse_move = !s->vars->get_mouse_move;
	if (kc == XK_L)
		inc_max_dep(s->vars);
	if (kc == XK_K)
		dec_max_dep(s->vars);
	if (kc == XK_R)
		toggle_rects(s->vars);
	return (second_key_press(kc, s));
}
