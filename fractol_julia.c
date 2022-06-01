/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_julia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:24:08 by tpeters           #+#    #+#             */
/*   Updated: 2022/06/01 04:21:31 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//https://theses.liacs.nl/pdf/2018-2019-JonckheereLSde.pdf
//http://www.nongnu.org/hpalib/
//https://scipython.com/book2/chapter-8-scipy/examples/the-newton-fractal/
//https://www.ibiblio.org/e-notes/MSet/TheAlmondBreadHomepage.htm
int	julia(struct s_fract_arguments *s)
{
	int		depth;
	double	tmp;

	depth = 0;
	while ((s->x * s->x + s->y * s->y <= 4) && depth < s->depth_max)
	{
		tmp = s->x * s->x - s->y * s->y + s->xn;
		s->y = 2 * s->x * s->y + s->yn;
		s->x = tmp;
		depth++;
	}
	return (depth);
}
