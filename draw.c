/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgreenpo <cgreenpo@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:16:06 by cgreenpo          #+#    #+#             */
/*   Updated: 2022/05/29 14:41:08 by cgreenpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

t_color	set_color(int iteration, t_fractol *base)
{
	t_color	color;
	double	n;

	n = (double)iteration / base->max_iter;
	if (n == 1)
	{
		color.channel[0] = 1;
		color.channel[1] = 255;
		color.channel[2] = 255;
		color.channel[3] = 255;
	}
	else
	{
		color.channel[0] = 1;
		color.channel[1] = (int)(150 * n * n * n);
		color.channel[2] = (int)(200 * n);
		color.channel[3] = (int)(255 * n);
	}
	return (color);
}

static void	put_pixel(t_fractol *fractol, int x, int y, t_color color)
{
	int	i;

	i = (x * fractol->image->bits_per_pixel / 8)
		+ (y * fractol->image->line_length);
	fractol->image->addr[i] = color.channel[3];
	fractol->image->addr[++i] = color.channel[2];
	fractol->image->addr[++i] = color.channel[1];
	fractol->image->addr[++i] = color.channel[0];
}

t_complex	init_complex(double re, double im)
{
	t_complex	complex;

	complex.x = re;
	complex.y = im;
	return (complex);
}

void	*draw(void *n)
{
	t_color			cl;
	t_calc			z;
	int				itr;
	t_fractol		*base;

	base = n;
	z.height = base->start_line;
	while (z.height < base->finish_line)
	{
		z.b = conv_h(z.height, (*base));
		z.width = 0;
		while (z.width < WIDTH)
		{
			itr = base->formula(base, z);
			cl = set_color(itr, base);
			put_pixel(base, z.width, z.height, cl);
			z.width++;
		}
		z.height++;
	}
	return (NULL);
}
