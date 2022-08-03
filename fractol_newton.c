/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_newton.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 04:17:43 by tpeters           #+#    #+#             */
/*   Updated: 2022/08/03 13:25:42 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	newton_f(double re, double im, int real)
{
	if (real)
		return (pow(re, 4) - 6 * pow(re, 2) * pow(im, 2) + pow(im, 4) - 1);
	return (4 * pow(re, 3) * im - 4 * re * pow(im, 3));
}

static double	newton_fp(double re, double im, int real)
{
	if (real)
		return (4 * (pow(re, 3) - 3 * re * pow(im, 2)));
	return (4 * (3 * pow(re, 2) * im - pow(im, 3)));
}

static double	root_dist(double re, double im, double re2, double im2)
{
	return (sqrt(pow(re2 - re, 2) + pow(im2 - im, 2)));
}

static int	root_closest(double re, double im)
{
	double	dist[4];

	dist[0] = root_dist(re, im, 0, 1);
	dist[1] = root_dist(re, im, 0, -1);
	dist[2] = root_dist(re, im, 1, 0);
	dist[3] = root_dist(re, im, -1, 0);
	if (dist[0] <= dist[1] && dist[0] <= dist[2] && dist[0] <= dist[3])
		return (1);
	if (dist[1] <= dist[2] && dist[1] <= dist[3] && dist[1] <= dist[0])
		return (2);
	if (dist[2] <= dist[1] && dist[2] <= dist[0] && dist[2] <= dist[3])
		return (3);
	if (dist[3] <= dist[1] && dist[3] <= dist[2] && dist[3] <= dist[0])
		return (4);
	return (0);
}

int	newton(struct s_fract_arguments *s)
{
	int		tmp;
	double	a;
	double	b;
	double	c;
	double	d;

	tmp = 0;
	while (tmp < s->depth_max)
	{
		a = newton_f(s->x, s->y, 1);
		b = newton_f(s->x, s->y, 0);
		c = newton_fp(s->x, s->y, 1);
		d = newton_fp(s->x, s->y, 0);
		s->x -= (a * c + b * d) / (pow(c, 2) + pow(d, 2));
		s->y -= (b * c - a * d) / (pow(c, 2) + pow(d, 2));
		tmp++;
	}
	return (root_closest(s->x, s->y));
}
