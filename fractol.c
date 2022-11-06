/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:31:34 by tpeters           #+#    #+#             */
/*   Updated: 2022/11/06 22:29:34 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	after_args(t_bounds b, int (*f)(struct s_fract_arguments *stuff), \
double xn, double yn, int is_newton)
{
	t_vars					vars;
	struct s_for_each_pixel	stuff;

	if (!init(&vars))
		return (0);
	set_bounds(&vars, b);
	stuff.f = f;
	vars.xn = xn;
	vars.yn = yn;
	stuff.vars = &vars;
	vars.get_mouse_move = 0;
	vars.max_depth = DEPTH_MAX;
	vars.is_newton = is_newton;
	vars.show_rects = 0;
	mlx_hook(vars.win, 6, 1L << 6, mouse_move, &vars);
	mlx_loop_hook(vars.mlx, for_each_pixel, &stuff);
	mlx_hook(vars.win, 2, 1L << 0, key_press, &stuff);
	mlx_hook(vars.win, 17, 0, quit, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

void	args_to_init(double *x0, double *y0, char *argv[], int *err)
{
	int	error;

	error = 0;
	*x0 = ft_atod(argv[2], &error);
	*y0 = ft_atod(argv[3], &error);
	if (error)
		*err = 0;
}

void	init_main_vars(t_bounds *b, int *cp, double *x, double *y)
{
	*cp = 1;
	*x = -0.752;
	*y = 0.152;
	b->a = 0 - (WIDTH / 320.0);
	b->b = 0 + (WIDTH / 320.0);
	b->c = 0 + (HEIGHT / 320.0);
	b->d = 0 - (HEIGHT / 320.0);
}

int	other_main_params(int argc, char *argv[], t_bounds b, int cp)
{
	if (!ft_strcmp(argv[1], "MANDELBROT"))
	{
		b.a = -1 - (WIDTH / 320.0);
		b.b = -1 + (WIDTH / 320.0);
		if (cp && argc == 2)
			return (after_args(b, mandel, 0, 0, 0));
	}
	else if (!ft_strcmp(argv[1], "NEWTON"))
		if (cp && argc == 2)
			return (after_args(b, newton, 0, 0, 1));
	return (0);
}

int	main(int argc, char *argv[])
{
	t_bounds	b;
	int			correct_params;
	double		x0;
	double		y0;

	init_main_vars(&b, &correct_params, &x0, &y0);
	if ((argc == 2 || argc == 4))
	{
		if (argc == 4)
			args_to_init(&x0, &y0, argv, &correct_params);
		if (!ft_strcmp(argv[1], "JULIA"))
		{
			if (correct_params)
				return (after_args(b, julia, x0, y0, 0));
		}
		else
			other_main_params(argc, argv, b, correct_params);
	}
	prnt_how_to_use();
	return (0);
}
