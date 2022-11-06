/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:44:20 by tpeters           #+#    #+#             */
/*   Updated: 2022/11/06 22:32:53 by tpeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# ifdef __APPLE__
#  include "mlx/mlx.h"
#  define XK_ESCAPE                      53
#  define XK_LEFT                        123
#  define XK_UP                          126
#  define XK_RIGHT                       124
#  define XK_DOWN                        125
#  define XK_P                           35
#  define XK_K							40
#  define XK_L							37
#  define XK_R							15
#  define XK_M							46
#  define XK_J							38
#  define XK_N							45
#  define LCLICK 1
#  define MCLICK 3
#  define RCLICK 2
#  define SCRL_UP 4
#  define SCRL_DWN 5
# endif
# ifdef unix
#  include "mlx_linux/mlx.h"
//get keycodes from keysym.h and copy them. (norminette)
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
# define DEPTH_MAX 50

// 0.0 < ZOOM < 1.0
# define ZOOM 0.5

//PIXEL - nach links; + nach rechts
# define MOVE 10

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
	int		**depths;
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
void	init_depth_array(int **in);
int		**alloc_depth(void);
void	free_depth(int **in);

/* FRACTOL_RECT_OPTIMIZATION.C */
int		fill_rec_bord(struct s_rect_args *s);
void	rec_box(struct s_rect_args *s);

/* FRACTOL_KEY.C */
int		key_press(int kc, struct s_for_each_pixel *s);

/* FRACTOL_MOUSE.C */
int		mouse_move(int x, int y, t_vars *vars);
int		mouse_hook(int button, int x, int y, t_vars *vars);

/* FRACTOL_BOUNDS.C */
void	set_bounds(t_vars *vars, t_bounds in);
void	calc_len(t_vars *vars);
void	inc_max_dep(t_vars *vars);
void	dec_max_dep(t_vars *vars);

/* FRACTOL_STUFF.C */
int		init(t_vars *v);
int		quit(t_vars *vars);
void	prnt_how_to_use(void);

#endif
