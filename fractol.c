/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:31:34 by tpeters           #+#    #+#             */
/*   Updated: 2022/05/12 22:27:36 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"




int	quit(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	return (0);
}

#include <stdio.h>
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
	//vars.xmin = -0.75458984375000037747582837255322374403476715087891;
	//vars.ymin = -0.06177734374999996336264018736983416602015495300293;
	//vars.xmax = -0.74677734375000037747582837255322374403476715087891;
	//vars.ymax = -0.06958984374999996336264018736983416602015495300293;
	//vars.x_len = (vars.xmax - vars.xmin);
	//vars.y_len = (vars.ymax - vars.ymin);
	
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
