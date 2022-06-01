/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_mandelbrot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:34:17 by tpeters           #+#    #+#             */
/*   Updated: 2022/05/31 22:41:24 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	check_trivial(double x, double y)
{
	double	q;

	if (x * x + 2 * x + 1 + y * y < 0.0625)
		return (1);
	q = (x - 0.25) * (x - 0.25) + y * y;
	if (q * (q + (x - 0.25)) < y * y * 0.25)
		return (1);
	return (0);
}

int	mandel(struct s_fract_arguments *s)
{
	int		depth;
	double	tmp;

	if (check_trivial(s->x, s->y))
		return (s->depth_max);
	depth = 0;
	while ((s->xn * s->xn + s->yn * s->yn <= 4) && depth < s->depth_max)
	{
		tmp = s->xn * s->xn - s->yn * s->yn + s->x;
		s->yn = 2 * s->xn * s->yn + s->y;
		s->xn = tmp;
		depth++;
	}
	return (depth);
}
