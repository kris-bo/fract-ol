/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgreenpo <cgreenpo@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:40:36 by cgreenpo          #+#    #+#             */
/*   Updated: 2022/05/29 14:55:49 by cgreenpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	move(int keycode, t_fractol *base)
{
	double		w;
	double		h;

	w = (base->vp.maxx - base->vp.minx);
	h = (base->vp.maxy - base->vp.miny);
	if (keycode == ARROW_U)
	{
		base->vp.maxy += h * 0.1;
		base->vp.miny += h * 0.1;
	}
	else if (keycode == ARROW_R)
	{
		base->vp.maxx += w * 0.1;
		base->vp.minx += w * 0.1;
	}
	else if (keycode == ARROW_D)
	{
		base->vp.maxy -= h * 0.1;
		base->vp.miny -= h * 0.1;
	}
	else if (keycode == ARROW_L)
	{
		base->vp.maxx -= w * 0.1;
		base->vp.minx -= w * 0.1;
	}
}

int	iter_change(int keycode, t_fractol *base)
{
	if (keycode == PLUS)
	{
		if (base->max_iter < 50)
			base->max_iter += 1;
		else if (base->max_iter < 10000000)
			base->max_iter = (int)(base->max_iter * 1.05);
	}
	if (keycode == MINUS)
	{
		if (base->max_iter > 50)
			base->max_iter = (int)(base->max_iter * 0.95);
		else if (base->max_iter > 1)
			base->max_iter -= 1;
	}
	return (0);
}

int	key_hook(int keycode, t_fractol *base)
{
	if (keycode == ESC)
		exit (0);
	if (keycode == ARROW_U || keycode == ARROW_D
		|| keycode == ARROW_L || keycode == ARROW_R)
		move(keycode, base);
	else if (keycode == PLUS || keycode == MINUS)
		iter_change(keycode, base);
	else if (keycode == SPACE)
	{
		if (base->julia_mv == 1)
			base->julia_mv = 0;
		else
			base->julia_mv = 1;
	}
	threading(base);
	return (0);
}
