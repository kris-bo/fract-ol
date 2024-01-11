/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgreenpo <cgreenpo@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:16:41 by cgreenpo          #+#    #+#             */
/*   Updated: 2022/05/29 14:51:01 by cgreenpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"
#include <stdio.h>

void	threading(t_fractol *base)
{
	pthread_t	threads[THREADS];
	t_fractol	bases[THREADS];
	int			i;

	i = 0;
	base->scales->re = (base->vp.maxx
			- base->vp.minx) / WIDTH;
	base->scales->im = (base->vp.maxy
			- base->vp.miny) / HEIGHT;
	while (i < THREADS)
	{
		bases[i] = *base;
		bases[i].start_line = i * (HEIGHT / THREADS);
		bases[i].finish_line = (i + 1) * (HEIGHT / THREADS);
		pthread_create(&threads[i], NULL, draw, (void *)&bases[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(base->mlx, base->window,
		base->image->img, 0, 0);
}

void	init_base(t_fractol *base)
{
	t_viewp		viewp;

	viewp.minx = -2.0;
	viewp.miny = -2.0;
	viewp.maxx = 2.0;
	viewp.maxy = 2.0;
	base->vp = viewp;
	base->k_re = -0.70;
	base->k_im = -0.38;
	base->julia_mv = 0;
	base->max_iter = 50;
}

void	arg_mng(int argc, char **argv, t_fractol *base)
{
	int		error;

	error = 0;
	if (argc != 2)
	{
		ft_putstr("Error: wrong number of arguments");
		error = 1;
	}
	else if (ft_strcmp(argv[1], "julia"))
		base->formula = &form_julia;
	else if (ft_strcmp(argv[1], "mandelbrot"))
		base->formula = &form_mand;
	else
	{
		ft_putstr("Error: invalid fractal name");
		error = 1;
	}
	if (error)
	{
		ft_putstr("\nAvailable options:\n1. julia\n2. mandelbrot\n");
		exit (0);
	}
}

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_scale		scale;
	t_fractol	base;

	arg_mng(argc, argv, &base);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "fract-ol");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	base.mlx = mlx;
	base.window = mlx_win;
	base.image = &img;
	init_base(&base);
	base.scales = &scale;
	mlx_key_hook(mlx_win, key_hook, &base);
	mlx_hook(base.window, 4, 0, scaling, &base);
	mlx_hook(base.window, 6, 0, julia_move, &base);
	threading(&base);
	mlx_loop(mlx);
	return (0);
}
