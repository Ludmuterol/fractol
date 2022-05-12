/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:31:34 by tpeters           #+#    #+#             */
/*   Updated: 2022/05/12 17:14:14 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandel(double x, double y)
{
	double	xn = 0, yn = 0;
	int		depth = 0;
	if (x * x + 2 * x + 1 + y * y < 0.0625)
		return (DEPTH_MAX);
	double q = (x - 0.25) * (x - 0.25) + y * y;
	if (q * (q + (x - 0.25)) < y * y * 0.25)
		return (DEPTH_MAX);
	while (depth <= DEPTH_MAX)
	{
		double xx = xn * xn;
		double yy = yn * yn;
		double tmp = xx - yy + x; 
		yn = 2 * xn * yn + y;
		xn = tmp;
		depth++;
		if (xx + yy > 4)
			return (depth);
	}
	return (depth);
}

void	testfunc(t_vars *vars, int x, int y, int i)
{
	if (vars->mand_depths[x][y] < DEPTH_MAX)
	{
		double tmp = (((double)vars->mand_depths[x][y]) / (128)) * 2 * M_PI + i / 5.0;
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

void	init_depth_array(int in[WIDTH][HEIGHT])
{
	int c, d;
	
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

void	move_array(t_vars *vars, int hor, int ver)
{
	int	tmp[WIDTH][HEIGHT];
	int c, d;
	
	init_depth_array(tmp);
	c = 0;
	while (c < WIDTH)
	{
		d = 0;
		while (d < HEIGHT)
		{
			
			if (hor && c + hor >= 0 && c + hor < WIDTH)
				tmp[c + hor][d] = vars->mand_depths[c][d];
			if (ver && d + ver >= 0 && d + ver < HEIGHT)
				tmp[c][d + ver] = vars->mand_depths[c][d];
			d++;
		}
		c++;
	}
	c = 0;
	while (c < WIDTH)
	{
		d = 0;
		while (d < HEIGHT)
		{
			vars->mand_depths[c][d] = tmp[c][d];
			d++;
		}
		c++;
	}
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
		mlx_loop_end(vars->mlx);
	if (keycode == XK_Right || keycode == XK_Left || keycode == XK_Up || keycode == XK_Down)
		{
			if (keycode == XK_Right)
			{
				vars->xmin += (vars->x_len / WIDTH) * MOVE;
				vars->xmax += (vars->x_len / WIDTH) * MOVE;
				move_array(vars,- MOVE, 0);
			}
			if (keycode == XK_Left)
			{
				vars->xmin -= (vars->x_len / WIDTH) * MOVE;
				vars->xmax -= (vars->x_len / WIDTH) * MOVE;
				move_array(vars, MOVE, 0);
			}
			if (keycode == XK_Up)
			{
				vars->ymin += (vars->y_len / HEIGHT) * MOVE;
				vars->ymax += (vars->y_len / HEIGHT) * MOVE;
				move_array(vars, 0, MOVE);
			}
			if (keycode == XK_Down)
			{
				vars->ymin -= (vars->y_len / HEIGHT) * MOVE;
				vars->ymax -= (vars->y_len / HEIGHT) * MOVE;
				move_array(vars, 0, - MOVE);
			}
			vars->x_len = (vars->xmax - vars->xmin);
			vars->y_len = (vars->ymax - vars->ymin);
		}
	return (0);
}

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
		vars->xmin = mouse_x - x_dist;
		vars->xmax = mouse_x + x_dist;
		vars->ymin = mouse_y - y_dist;
		vars->ymax = mouse_y + y_dist;
		vars->x_len = (vars->xmax - vars->xmin);
		vars->y_len = (vars->ymax - vars->ymin);
		int c = 0, d = 0;
		while (c < WIDTH)
		{
			d = 0;
			while (d < HEIGHT)
			{
				vars->mand_depths[c][d] = -1;
				d++;
			}
			c++;
		}
	}
	return (0);
}

#include <stdlib.h>
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
	
	init_depth_array(vars.mand_depths);

	vars.xmin = -1 - (WIDTH / 320);
	vars.xmax = -1 + (WIDTH / 320);
	vars.ymin = 0 + (HEIGHT / 320);
	vars.ymax = 0 - (HEIGHT / 320);
	vars.x_len = (vars.xmax - vars.xmin);
	vars.y_len = (vars.ymax - vars.ymin);
	
	mlx_loop_hook (vars.mlx, for_each_pixel, &vars);
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
