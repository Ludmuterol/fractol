/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:44:20 by tpeters           #+#    #+#             */
/*   Updated: 2022/08/04 20:04:40 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H


# ifdef _WIN32
# endif
# ifdef __APPLE__
#  include "mlx/mlx.h"
#  define XK_Escape                      53
#  define XK_Left                        123
#  define XK_Up                          126
#  define XK_Right                       124
#  define XK_Down                        125
#  define XK_p                           35
#  define XK_k							40
#  define XK_l							37
#  define XK_r							15
#  define XK_m							46
#  define XK_j							38
#  define XK_n							45
#  define LCLICK 1
#  define MCLICK 3
#  define RCLICK 2
#  define SCRL_UP 4
#  define SCRL_DWN 5
# endif
# ifdef unix
#  include "mlx_linux/mlx.h"
#  include <X11/keysym.h>
#  define LCLICK 1
#  define MCLICK 2
#  define RCLICK 3
#  define SCRL_UP 4
#  define SCRL_DWN 5
# endif

# include <math.h>
# include <stdlib.h>
# include "libft/libft.h"

# define HEIGHT 500
# define WIDTH 500
# define DEPTH_MAX 500

# define ZOOM 0.5	// 0.0 < ZOOM < 1.0
# define MOVE 11	//PIXEL - nach links; + nach rechts

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endi;
}	t_data;

typedef struct s_vars
{
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
	int		max_depth;
	int		depths[WIDTH][HEIGHT];
	int		get_mouse_move;
	int		is_newton;
	int		show_rects;
}	t_vars;

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

struct s_fract_arguments
{
	int		depth_max;
	double	x;
	double	y;
	double	xn;
	double	yn;
};

struct s_rect_args
{
	struct s_for_each_pixel	*stuff;
	int						x1;
	int						y1;
	int						x2;
	int						y2;
};

struct s_for_each_pixel
{
	t_vars	*vars;
	int		(*f)(struct s_fract_arguments *stuff);
};

typedef struct s_bounds
{
	double	a;
	double	b;
	double	c;
	double	d;
}	t_bounds;

/* FRACTOL_COLOR_UTILS.C */
t_color	new_color(unsigned char r, unsigned char g, unsigned char b, int endi);
void	put_pixel(t_data *img, int x, int y, t_color color);
void	fill_rec(struct s_rect_args *s, int value);
t_color	depth_to_col(t_vars *vars, double dep, int i);

/* FRACTOL_MANDELBROT.C */
int		mandel(struct s_fract_arguments *s);

/* FRACTOL_JULIA.c */
int		julia(struct s_fract_arguments *s);

/* FRACTOL_NEWTON.C */
int		newton(struct s_fract_arguments *s);

/* FRACTOL_PIXEL_UTILS.C */
int		coord_to_offset(int x, int y, int line_length, int bits_per_pixel);
int		for_each_pixel(struct s_for_each_pixel *stuff);
void	put_pixels(t_vars *vars, int x, int y, int i);

/* FRACTOL_DEPTH_ARRAY.C */
void	move_array(t_vars *vars, int hor, int ver);
void	init_depth_array(int in[WIDTH][HEIGHT]);

/* FRACTOL_RECT_OPTIMIZATION.C */
int		fill_rec_bord(struct s_rect_args *s);
void	rec_box(struct s_rect_args *s);

#endif
