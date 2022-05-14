/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:44:20 by tpeters           #+#    #+#             */
/*   Updated: 2022/05/14 17:32:23 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# ifdef _WIN32
# endif
# ifdef __APPLE__
# include "mlx/mlx.h"
# define XK_Escape                        53
# define XK_Left                          123
# define XK_Up                            126
# define XK_Right                         124
# define XK_Down                          125
# define XK_p                             35
# define LCLICK 1
# define MCLICK 3
# define RCLICK 2
# define SCRL_UP 4
# define SCRL_DWN 5
# endif
# ifdef unix
# include "mlx_linux/mlx.h"
# include <X11/keysym.h>
# define LCLICK 1
# define MCLICK 2
# define RCLICK 3
# define SCRL_UP 4
# define SCRL_DWN 5
# endif

# include <math.h>
# include <stdlib.h>



# define HEIGHT 800
# define WIDTH 800
# define DEPTH_MAX 255

# define ZOOM 0.5	// 0.0 < ZOOM < 1.0
# define MOVE 10	//PIXEL - nach links; + nach rechts

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
	double	x_len;
	double	y_len;
	double	xmin;
	double	xmax;
	double	ymin;
	double	ymax;
	double	xn;
	double	yn;
	int		depths[WIDTH][HEIGHT];
	int		get_mouse_move;
}				t_vars;

struct s_for_each_pixel
{
	t_vars	*vars;
	int (*f)(double x, double y, double xn, double yn);
};

/* FRACTOL_COLOR_UTILS.C */
t_color	new_color(unsigned char t, unsigned char r, unsigned char g, unsigned char b, int endian);
void	put_pixel(t_data *img, int x, int y, t_color color);
t_color hsv2rgb(t_color HSV, int endian);

/* FRACTOL_PIXEL_UTILS.C */
int		coord_to_offset(int x, int y, int line_length, int bits_per_pixel);
int		for_each_pixel(struct s_for_each_pixel *stuff);
void	put_pixels(t_vars *vars, int x, int y, int i);

/* FRACTOL_MANDELBROT.C */
int		mandel(double x, double y, double xn, double yn);

/* FRACTOL_JULIA.c */
int		julia(double xn, double yn, double x, double y);

/* FRACTOL_DEPTH_ARRAY.C */
void	move_array(t_vars *vars, int hor, int ver);
void	init_depth_array(int in[WIDTH][HEIGHT]);

#endif
