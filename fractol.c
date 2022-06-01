/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:31:34 by tpeters           #+#    #+#             */
/*   Updated: 2022/06/01 04:13:48 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	quit(t_vars *vars)
{
	exit(0);
	return (0);
}

void	calc_len(t_vars *vars)
{
	vars->x_len = (vars->xmax - vars->xmin);
	vars->y_len = (vars->ymax - vars->ymin);
}

void	set_bounds(t_vars *vars, double a, double b, double c, double d)
{
	vars->xmin = a;
	vars->xmax = b;
	vars->ymin = c;
	vars->ymax = d;
	calc_len(vars);
}

void	inc_max_dep(t_vars *vars)
{
	int	c;
	int	d;

	c = 0;
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

int	key_press(int kc, t_vars *vars)
{
	double	tmp;

	if (kc == XK_Escape)
		exit(0);
	if (kc == XK_Left || kc == XK_Down || kc == XK_Up || kc == XK_Right)
	{
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
	if (kc == XK_p)
	{
		if (vars->get_mouse_move)
			vars->get_mouse_move = 0;
		else
			vars->get_mouse_move = 1;
	}
	if (kc == XK_l)
		inc_max_dep(vars);
	if (kc == XK_k)
		dec_max_dep(vars);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	double	x_dist;
	double	y_dist;
	double	mouse_x;
	double	mouse_y;

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
		mouse_x = vars->xmin + (((double)x / WIDTH) * vars->x_len);
		mouse_y = vars->ymax - (((double)y / HEIGHT) * vars->y_len);
		set_bounds(vars, mouse_x - x_dist, mouse_x + x_dist, mouse_y - y_dist, mouse_y + y_dist);
		init_depth_array(vars->depths);
	}
	return (0);
}

int	init(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (0);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Hello world!");
	if (!vars->win)
		return (0);
	vars->img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->img.img)
		return (mlx_destroy_window(vars->mlx, vars->win));
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bpp, &vars->img.line_length, &vars->img.endian);
	if (!vars->img.addr)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		return (mlx_destroy_image(vars->mlx, vars->img.img));
	}
	init_depth_array(vars->depths);
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

//set_bounds(&vars, -0.7545898, -0.7467773, -0.0617773, -0.0695898);
//set_bounds(&vars, −0.7475087485, −0.7475087322, 0.0830715266, 0.0830715359)
int	main(void)
{
	t_vars					vars;
	struct s_for_each_pixel	stuff;

	if (!init(&vars))
		return (0);
	vars.is_newton = 0;
	//set_bounds(&vars, -1 - (WIDTH / 320.0), -1 + (WIDTH / 320.0), 0 + (HEIGHT / 320.0), 0 - (HEIGHT / 320.0));
	//stuff.f = mandel;
	//vars.xn = 0;
	//vars.yn = 0;
	set_bounds(&vars, -2, 2, -2, 2);
	stuff.f = julia;
	vars.xn = 0.1627;
	vars.yn = 0.5717;
	//set_bounds(&vars, -1, 1, -1, 1);
	//stuff.f = newton;
	//vars.xn = 0.1627;
	//vars.yn = 0.5717;
	//vars.is_newton = 1;

	stuff.vars = &vars;
	vars.get_mouse_move = 0;
	vars.max_depth = DEPTH_MAX;
	mlx_hook(vars.win, 6, 1L << 6, mouse_move, &vars);

	mlx_loop_hook(vars.mlx, for_each_pixel, &stuff);
	mlx_hook(vars.win, 2, 1L << 0, key_press, &vars);
	mlx_hook(vars.win, 17, 0, quit, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
