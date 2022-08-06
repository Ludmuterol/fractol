/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_depth_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:08:41 by tpeters           #+#    #+#             */
/*   Updated: 2022/08/06 21:19:47 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_depth_array(int **in)
{
	int	c;
	int	d;

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
	int	c;
	int	d;

	if (hor <= 0)
		c = 0;
	else
		c = WIDTH - 1;
	while (c >= 0 && c < WIDTH)
	{
		if (ver <= 0)
			d = 0;
		else
			d = HEIGHT - 1;
		while (d >= 0 && d < HEIGHT)
		{
			if (c - hor >= 0 && c - hor < WIDTH && \
				d - ver >= 0 && d - ver < HEIGHT)
				vars->depths[c][d] = vars->depths[c - hor][d - ver];
			else
				vars->depths[c][d] = -1;
			d += -1 + (ver <= 0) * 2;
		}
		c += -1 + (hor <= 0) * 2;
	}
}

int	**alloc_depth(void)
{
	int	**tmp;
	int	c;

	tmp = (int **)malloc(sizeof(int *) * WIDTH);
	if (!tmp)
		return (NULL);
	c = 0;
	while (c < WIDTH)
	{
		tmp[c] = (int *)malloc(sizeof(int) * HEIGHT);
		if (!tmp)
		{
			while (c > 0)
			{
				free(tmp[c - 1]);
				c--;
			}
			free(tmp);
			return (NULL);
		}
		c++;
	}
	return (tmp);
}

void	free_depth(int **in)
{
	int	c;

	c = 0;
	while (c < WIDTH)
	{
		free(in[c]);
		c++;
	}
	free(in);
}
