/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:31:34 by tpeters           #+#    #+#             */
/*   Updated: 2022/05/12 03:59:12 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void next_step(double *x, double *y, double x1, double y1)
{
	//xn+1 = xn²-yn² + x1 und yn+1 = 2*xn*yn+ y1 und an+1 = SQRT(xn+1² + yn+1²)
	double tmp = *x * *x - *y * *y + x1; 
	*y = 2 * *x * *y + y1;
	*x = tmp;
}

int	mandel(double x, double y)
{
	double	xn = 0, yn = 0;
	int		depth = 0;
	while (sqrt(xn * xn + yn * yn) <= 2 && depth <= DEPTH_MAX)
	{
		next_step(&xn, &yn, x, y);
		depth++;
	}
	return (depth);
}

void	testfunc(t_vars *vars, int x, int y, int i)
{
	double xtrans = vars->xmin + ((double)x / WIDTH) * (vars->xmax - vars->xmin);
	double ytrans = vars->ymax - ((double)y / HEIGHT) * (vars->ymax - vars->ymin);
	int depth = mandel(xtrans, ytrans);
	if (depth < DEPTH_MAX)
	{
		double tmp = (((double)depth) / (128)) * 2 * M_PI + i / 5.0;
		put_pixel(&vars->img, x, y, new_color(0, (sin(tmp) + 1) * 255/2, (sin(tmp + 2) + 1) * 255/2, (sin(tmp + 4) + 1) * 255/2, vars->img.endian));
	}
	else
		put_pixel(&vars->img, x, y, new_color(0, 0, 0, 0, vars->img.endian));
}

int	quit(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	return (0);
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
		mlx_loop_end(vars->mlx);
	return (0);
}
#include <stdio.h>
int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	double x_dist;
	double y_dist;
	double mouse_x;
	double mouse_y;

	if (button == SCRL_UP || button == SCRL_DWN)
	{
		if (button == SCRL_UP)
		{
			x_dist = ((vars->xmax - vars->xmin) * ZOOM) / 2;
			y_dist = ((vars->ymax - vars->ymin) * ZOOM) / 2;
		}
		else
		{
			x_dist = ((vars->xmax - vars->xmin) / ZOOM) / 2;
			y_dist = ((vars->ymax - vars->ymin) / ZOOM) / 2;
		}
		mouse_x = vars->xmin + (((double)x / WIDTH) * (vars->xmax - vars->xmin));
		mouse_y = vars->ymax - (((double)y / HEIGHT) * (vars->ymax - vars->ymin));
		vars->xmin = mouse_x - x_dist;
		vars->xmax = mouse_x + x_dist;
		vars->ymin = mouse_y - y_dist;
		vars->ymax = mouse_y + y_dist;
	}
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (0);
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello world!");
	if (!vars.win)
		return (0);
	vars.img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	if (!vars.img.img)
		return (0);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	if (!vars.img.addr)
		return (0);
	//-3 < x < 2 und -2 < y < 2
	vars.xmin = -3;
	vars.xmax = 1;
	vars.ymin = -2;
	vars.ymax = 2;
	//- 0.37465401 < x < - 0,37332411 und +0.659227668 < y < +0,66020767
	//vars.xmin = -0.37465401;
	//vars.xmax = -0.37332411;
	//vars.ymin = +0.659227668;
	//vars.ymax = +0.66020767;

	struct s_for_each_pixel_params tmp;
	tmp.vars = &vars;
	tmp.func = testfunc;
	
	mlx_loop_hook (vars.mlx, for_each_pixel, &tmp);
	//for_each_pixel(&tmp);
	mlx_hook(vars.win, 2, 1L<<0, key_press, &vars);
	mlx_hook(vars.win, 17, 0, quit, &vars);
	mlx_mouse_hook (vars.win, mouse_hook, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	
	
	mlx_loop(vars.mlx);
	mlx_destroy_image(vars.mlx, vars.img.img);
	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	return (0);
}
