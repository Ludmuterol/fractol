/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_julia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:24:08 by tpeters           #+#    #+#             */
/*   Updated: 2022/05/15 04:03:37 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//https://theses.liacs.nl/pdf/2018-2019-JonckheereLSde.pdf
//http://www.nongnu.org/hpalib/
//https://scipython.com/book2/chapter-8-scipy/examples/the-newton-fractal/
int	julia(double xn, double yn, double x, double y)
{
	int		depth;
	double	tmp;

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
