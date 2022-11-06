/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:27:51 by tpeters           #+#    #+#             */
/*   Updated: 2022/11/06 22:32:58 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	prnt_how_to_use(void)
{
	ft_printf("fractol MODE\n");
	ft_printf("Possible Values for MODE:\n");
	ft_printf("\tMANDELBROT\n");
	ft_printf("\tJULIA [X0 Y0]\n");
	ft_printf("\tNEWTON\n");
	ft_printf("X0, Y0 as floats and only for JULIA\n");
	exit(0);
}

int	quit(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->win);
	if (vars->depths)
		free_depth(vars->depths);
	exit(0);
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
	v->depths = alloc_depth();
	if (!v->depths)
		quit(v);
	init_depth_array(v->depths);
	return (1);
}
