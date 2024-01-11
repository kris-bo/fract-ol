/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgreenpo <cgreenpo@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:16:23 by cgreenpo          #+#    #+#             */
/*   Updated: 2022/05/29 14:41:08 by cgreenpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

# include <math.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include "miniLibX/mlx.h"

# define WIDTH				1000
# define HEIGHT				1000
# define THREADS			10
# define ESC				53
# define ZOOM_IN			4
# define ZOOM_OUT			5
# define ARROW_U			126
# define ARROW_D			125
# define ARROW_L			123
# define ARROW_R			124
# define SPACE				49
# define PLUS				24
# define MINUS				27

typedef struct s_scale
{
	double	re;
	double	im;
}	t_scale;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_viewp
{
	double	minx;
	double	miny;
	double	maxx;
	double	maxy;
}	t_viewp;

typedef struct s_complex
{
	double			x;
	double			y;
}					t_complex;

typedef struct s_calc
{
	double		cx;
	double		cy;
	double		new_a;
	double		new_b;
	double		b;
	double		a;
	int			height;
	int			width;
}	t_calc;

typedef struct s_color
{
	int			channel[4];
}	t_color;

typedef struct s_fractol	t_fractol;

typedef int					(*t_ft)(t_fractol *base, t_calc z);

struct	s_fractol
{
	void		*mlx;
	void		*window;
	t_data		*image;
	t_viewp		vp;
	t_scale		*scales;
	int			start_line;
	int			finish_line;
	int			max_iter;
	double		k_re;
	double		k_im;
	int			julia_mv;
	t_ft		formula;
};

int			form_julia(struct s_fractol *base, t_calc z);
int			form_mand(struct s_fractol *base, t_calc z);
int			key_hook(int keycode, t_fractol *base);
void		threading(t_fractol *fractol);
void		*draw(void *n);
int			julia_move(int x, int y, t_fractol *base);
int			scaling(int keycode, int x, int y, t_fractol *base);
static void	put_pixel(t_fractol *fractol, int x, int y, t_color color);
double		conv_w(int num, t_fractol base);
double		conv_h(int num, t_fractol base);
t_complex	init_complex(double re, double im);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_putstr(char *s);

#endif