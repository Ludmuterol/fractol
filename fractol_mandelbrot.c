/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_mandelbrot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:34:17 by tpeters           #+#    #+#             */
/*   Updated: 2022/05/15 03:35:06 by tpeters          ###   ########.fr       */
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

//https://theses.liacs.nl/pdf/2018-2019-JonckheereLSde.pdf
//http://www.nongnu.org/hpalib/
int	mandel(double x, double y, double xn, double yn)
{
	int		depth;
	double	tmp;

	//if (check_trivial(x, y))
	//	return (DEPTH_MAX);
	depth = 0;
	while ((xn * xn + yn * yn <= 4) && depth < DEPTH_MAX)
	{
		tmp = xn * xn - yn * yn + x;
		yn = 2 * xn * yn + y;
		xn = tmp;
		depth++;
	}
	return (depth);
}
