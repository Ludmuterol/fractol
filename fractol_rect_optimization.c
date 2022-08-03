/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_rect_optimization.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 22:39:26 by tpeters           #+#    #+#             */
/*   Updated: 2022/08/03 17:45:35 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	check_coord(int val, int *check, int *ret)
{
	if (*ret && *check != val)
	{
		if (*check == -1)
			*check = val;
		else
			*ret = 0;
	}
}

static int	fill_coord(struct s_rect_args *s, int x, int y)
{
	struct s_fract_arguments	fs;

	if (s->stuff->vars->depths[x][y] == -1)
	{
		fs.depth_max = s->stuff->vars->max_depth;
		fs.x = s->stuff->vars->xmin;
		fs.x += ((double)x / WIDTH) * s->stuff->vars->x_len;
		fs.y = s->stuff->vars->ymax;
		fs.y -= ((double)y / HEIGHT) * s->stuff->vars->y_len;
		fs.xn = s->stuff->vars->xn;
		fs.yn = s->stuff->vars->yn;
		s->stuff->vars->depths[x][y] = s->stuff->f(&fs);
	}
	return (s->stuff->vars->depths[x][y]);
}

int	fill_rec_bord(struct s_rect_args *s)
{
	int	check;
	int	ret;
	int	tmp;

	check = -1;
	ret = 1;
	tmp = 0;
	while ((s->x1 + tmp <= s->x2) || (s->y1 + tmp <= s->y2))
	{
		if (s->x1 + tmp <= s->x2)
		{
			check_coord(fill_coord(s, s->x1 + tmp, s->y1), &check, &ret);
			check_coord(fill_coord(s, s->x1 + tmp, s->y2), &check, &ret);
		}
		if (s->y1 + tmp <= s->y2)
		{
			check_coord(fill_coord(s, s->x1, s->y1 + tmp), &check, &ret);
			check_coord(fill_coord(s, s->x2, s->y1 + tmp), &check, &ret);
		}
		tmp++;
	}
	if (ret && ((check > 1 && s->stuff->f == mandel) || s->stuff->f != mandel))
		return (check);
	return (0);
}

//rec_box(stuff, x1, y1, x1 + (x2 - x1) / 2, y1 + (y2 - y1) / 2);
//rec_box(stuff, x1 + (x2 - x1) / 2, y1, x2, y1 + (y2 - y1) / 2);
//rec_box(stuff, x1, y1 + (y2 - y1) / 2, x1 + (x2 - x1) / 2, y2);
//rec_box(stuff, x1 + (x2 - x1) / 2, y1 + (y2 - y1) / 2, x2, y2);
static void	rec_rec_box_call(struct s_rect_args *s)
{
	struct s_rect_args	stuff;

	stuff.stuff = s->stuff;
	stuff.x1 = s->x1;
	stuff.y1 = s->y1;
	stuff.x2 = s->x1 + (s->x2 - s->x1) / 2;
	stuff.y2 = s->y1 + (s->y2 - s->y1) / 2;
	rec_box(&stuff);
	stuff.x1 = s->x1 + (s->x2 - s->x1) / 2;
	stuff.x2 = s->x2;
	rec_box(&stuff);
	stuff.x1 = s->x1;
	stuff.y1 = s->y1 + (s->y2 - s->y1) / 2;
	stuff.x2 = s->x1 + (s->x2 - s->x1) / 2;
	stuff.y2 = s->y2;
	rec_box(&stuff);
	stuff.x1 = s->x1 + (s->x2 - s->x1) / 2;
	stuff.x2 = s->x2;
	rec_box(&stuff);
}

//change fill_rec(s, tmp) to fill_rec(s, 5)
void	rec_box(struct s_rect_args *s)
{
	int					tmp;

	tmp = fill_rec_bord(s);
	if (tmp)
		fill_rec(s, tmp);
	else
	{
		if (s->x2 - s->x1 < 5 || s->y2 - s->y1 < 5)
			return ;
		rec_rec_box_call(s);
	}
}
