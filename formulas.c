/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formulas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgreenpo <cgreenpo@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:16:12 by cgreenpo          #+#    #+#             */
/*   Updated: 2022/05/29 14:41:08 by cgreenpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	form_julia(struct s_fractol *base, t_calc z)
{
	int			itr;
	double		res;

	itr = 0;
	z.a = conv_w(z.width, (*base));
	while (itr < (*base).max_iter)
	{
		z.new_a = ((z.a * z.a) - (z.b * z.b));
		z.new_b = 2 * z.a * z.b;
		z.a = z.new_a + (*base).k_re;
		z.b = z.new_b + (*base).k_im;
		res = z.a + z.b;
		if (res * res > 4)
			break ;
		itr++;
	}
	return (itr);
}

int	form_mand(struct s_fractol *base, t_calc z)
{
	int			itr;
	double		res;

	itr = 0;
	z.a = conv_w(z.width, (*base));
	z.cx = z.a ;
	z.cy = z.b;
	while (itr < (*base).max_iter)
	{
		z.new_a = ((z.a * z.a) - (z.b * z.b));
		z.new_b = 2 * z.a * z.b;
		z.a = z.new_a + z.cx;
		z.b = z.new_b + z.cy;
		res = z.a + z.b;
		if (res * res > 4)
			break ;
		itr++;
	}
	return (itr);
}
