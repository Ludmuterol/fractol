/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:44:20 by tpeters           #+#    #+#             */
/*   Updated: 2022/05/12 03:59:36 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
# include "mlx_linux/mlx.h"
# include <math.h>
# include <X11/keysym.h>

# define HEIGHT 800
# define WIDTH 800
# define DEPTH_MAX 50

# define ZOOM 0.5	// 0.0 < ZOOM < 1.0
/*
WIN mouse keys
*/
# define LCLICK 1
# define MCLICK 2
# define RCLICK 3
# define SCRL_UP 4
# define SCRL_DWN 5

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef union u_color
{
	struct
	{
		unsigned char	t;
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;
	};
	int	color;
}	t_color;


typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_data	img;
	double	xmin;
	double	xmax;
	double	ymin;
	double	ymax;
}				t_vars;


struct s_for_each_pixel_params{
	t_vars	*vars;
	void	(*func)(t_vars *vars, int x, int y, int i);
};

/* FRACTOL_COLOR_UTILS.C */
t_color	new_color(unsigned char t, unsigned char r, unsigned char g, unsigned char b, int endian);
void	put_pixel(t_data *img, int x, int y, t_color color);
t_color hsv2rgb(t_color HSV, int endian);

/* FRACTOL_PIXEL_UTILS.C */
int		coord_to_offset(int x, int y, int line_length, int bits_per_pixel);
int		for_each_pixel(struct s_for_each_pixel_params *input);

#endif
