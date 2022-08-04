/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:31:34 by tpeters           #+#    #+#             */
/*   Updated: 2022/08/04 20:11:47 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	quit(t_vars *vars)
{
	//mlx_destroy_window(vars->mlx, vars->win);
	//mlx_destroy_image(vars->mlx, vars->img.img);
	exit(vars->is_newton);
	return (0);
}

void	calc_len(t_vars *vars)
{
	vars->x_len = (vars->xmax - vars->xmin);
	vars->y_len = (vars->ymax - vars->ymin);
}

void	set_bounds(t_vars *vars, t_bounds in)
{
	vars->xmin = in.a;
	vars->xmax = in.b;
	vars->ymin = in.c;
	vars->ymax = in.d;
	calc_len(vars);
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
	if (vars->max_depth < 10)
		vars->max_depth += 1;
	else if (vars->max_depth < 50)
		vars->max_depth += 5;
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

void	arrow_key_press(int kc, t_vars *vars)
{
	double	tmp;

	if (kc == XK_Right || kc == XK_Left)
	{
		tmp = (vars->x_len / WIDTH) * MOVE * (1 - (kc == XK_Left) * 2);
		vars->xmin += tmp;
		vars->xmax += tmp;
		move_array(vars, -MOVE + 2 * MOVE * (kc == XK_Left), 0);
	}
	if (kc == XK_Up || kc == XK_Down)
	{
		tmp = (vars->y_len / HEIGHT) * MOVE * (1 - ((kc == XK_Down) * 2));
		vars->ymin += tmp;
		vars->ymax += tmp;
		move_array(vars, 0, MOVE - 2 * MOVE * (kc == XK_Down));
	}
	calc_len(vars);
}

void	toggle_rects(t_vars *vars)
{
	vars->show_rects = !vars->show_rects;
	init_depth_array(vars->depths);
}

int	key_press(int kc, struct s_for_each_pixel *s)
{
	if (kc == XK_Escape)
		exit(0);
	if (kc == XK_Left || kc == XK_Down || kc == XK_Up || kc == XK_Right)
		arrow_key_press(kc, s->vars);
	if (kc == XK_p)
		s->vars->get_mouse_move = !s->vars->get_mouse_move;
	if (kc == XK_l)
		inc_max_dep(s->vars);
	if (kc == XK_k)
		dec_max_dep(s->vars);
	if (kc == XK_r)
		toggle_rects(s->vars);
	if (kc == XK_m)
	{
		s->f = mandel;
		s->vars->is_newton = 0;
		init_depth_array(s->vars->depths);
	}
	if (kc == XK_j)
	{
		s->f = julia;
		s->vars->is_newton = 0;
		init_depth_array(s->vars->depths);
	}
	if (kc == XK_n)
	{
		s->f = newton;
		s->vars->is_newton = 1;
		init_depth_array(s->vars->depths);
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

int	init(t_vars *v)
{
	v->mlx = mlx_init();
	if (!v->mlx)
		return (0);
	v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, "Fractol");
	if (!v->win)
		return (0);
	v->img.img = mlx_new_image(v->mlx, WIDTH, HEIGHT);
	if (!v->img.img)
		return (mlx_destroy_window(v->mlx, v->win));
	v->img.addr = mlx_get_data_addr(v->img.img, &v->img.bpp, \
									&v->img.ll, &v->img.endi);
	if (!v->img.addr)
	{
		mlx_destroy_window(v->mlx, v->win);
		return (mlx_destroy_image(v->mlx, v->img.img));
	}
	init_depth_array(v->depths);
	return (1);
}

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

int	after_args(t_bounds b, int (*f)(struct s_fract_arguments *stuff), double xn, double yn, int is_newton)
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

#include <stdio.h>
void	prnt_how_to_use()
{
	printf("fractol MODE [XMIN XMAX YMIN YMAX]\n");
	printf("Possible Values for MODE:\n");
	printf("\tMANDELBROT\n");
	printf("\tJULIA\n");
	printf("\tNEWTON\n");
	printf("XMIN, XMAX, YMIN, YMAX as floats\n");
	printf("\t whole numbers: e.g fractol MANDELBROT -2. 2. -2. 2.\n");
	exit(0);
}

void	args_to_bounds(t_bounds *b, char *argv[], int *err)
{
	int	error;

	error = 0;
	b->a = ft_atod(argv[2], &error);
	b->b = ft_atod(argv[3], &error);
	b->c = ft_atod(argv[4], &error);
	b->d = ft_atod(argv[5], &error);
	if (error)
		*err = 0;
	printf("%lf, %lf, %lf, %lf\n", b->a, b->b, b->c, b->d);
}

//set_bounds(&vars, -0.7545898 -0.7467773 -0.0617773 -0.0695898);
//set_bounds(&vars, −0.7475087485 −0.7475087322 0.0830715266 0.0830715359)
int	main(int argc, char *argv[])
{
	t_bounds	b;
	int			correct_params;

	correct_params = 1;	
	if ((argc == 2 || argc == 6))
	{
		if (!ft_strcmp(argv[1], "MANDELBROT"))
		{
			if (argc == 6)
				args_to_bounds(&b, argv, &correct_params);
			else
			{
				b.a = -1 - (WIDTH / 320.0);
				b.b = -1 + (WIDTH / 320.0);
				b.c = 0 + (HEIGHT / 320.0);
				b.d = 0 - (HEIGHT / 320.0);
			}
			if (correct_params)
				return (after_args(b, mandel, 0, 0, 0));
		} else if (!ft_strcmp(argv[1], "JULIA"))
		{
			if (argc == 6)
				args_to_bounds(&b, argv, &correct_params);
			else
			{
				b.a = -2;
				b.b = 2;
				b.c = -2;
				b.d = 2;
			}
			if (correct_params)
				return (after_args(b, julia, 0.1627, 0.5717, 0));
		} else if (!ft_strcmp(argv[1], "NEWTON"))
		{
			if (argc == 6)
				args_to_bounds(&b, argv, &correct_params);
			else
			{
				b.a = -1;
				b.b = 1;
				b.c = -1;
				b.d = 1;
			}
			if (correct_params)
				return (after_args(b, newton, 0, 0, 1));
		}
	}
	prnt_how_to_use();
	return (0);
}
