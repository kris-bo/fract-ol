/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgreenpo <cgreenpo@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:41:36 by cgreenpo          #+#    #+#             */
/*   Updated: 2022/05/29 14:55:49 by cgreenpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

t_complex	get_shift(t_fractol *base, double zoom, t_complex px, t_fractol tmp)
{
	t_complex		new;
	t_complex		old;
	t_complex		shift;
	t_scale			scales_tmp;

	tmp = *base;
	tmp.vp.maxx *= zoom;
	tmp.vp.maxy *= zoom;
	tmp.vp.minx *= zoom;
	tmp.vp.miny *= zoom;
	scales_tmp.re = (tmp.vp.maxx
			- tmp.vp.minx) / WIDTH;
	scales_tmp.im = (tmp.vp.maxy
			- tmp.vp.miny) / HEIGHT;
	tmp.scales = &scales_tmp;
	old.x = conv_w(px.x, *base);
	old.y = conv_h(px.y, *base);
	new.x = conv_w(px.x, tmp);
	shift.x = old.x - new.x;
	new.y = conv_h(px.y, tmp);
	shift.y = old.y - new.y;
	return (shift);
}

int	scaling(int keycode, int x, int y, t_fractol *base)
{
	double			zoom;
	t_complex		shift;
	t_complex		px;
	t_fractol		tmp;

	if (keycode == ZOOM_IN || keycode == ZOOM_OUT)
	{
		if (keycode == ZOOM_IN)
			zoom = 0.80;
		else
			zoom = 1.20;
		tmp = *base;
		px.x = x;
		px.y = y;
		shift = get_shift(base, zoom, px, tmp);
		base->vp.maxx = base->vp.maxx * zoom + shift.x;
		base->vp.minx = base->vp.minx * zoom + shift.x;
		base->vp.maxy = base->vp.maxy * zoom + shift.y;
		base->vp.miny = base->vp.miny * zoom + shift.y;
		threading(base);
	}
	return (0);
}

int	julia_move(int x, int y, t_fractol *base)
{
	if (base->julia_mv == 1)
	{
		(*base).k_re = conv_w(x, *base);
		(*base).k_im = conv_h(y, *base);
		threading(base);
	}
	return (0);
}
