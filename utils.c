/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgreenpo <cgreenpo@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:17:02 by cgreenpo          #+#    #+#             */
/*   Updated: 2022/05/29 14:19:52 by cgreenpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (s2[j])
		j++;
	while (s1[i])
		i++;
	if (j != i)
		return (0);
	j = 0;
	while (s1[j] && s2[j])
	{
		if (s1[j] != s2[j])
			return (0);
		j++;
	}
	return (1);
}

void	ft_putstr(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	write(0, s, i);
}

double	conv_w(int num, t_fractol base)
{
	double		res;

	res = base.vp.minx + num * base.scales->re;
	return (res);
}

double	conv_h(int num, t_fractol base)
{
	double		res;

	res = base.vp.maxy - num * base.scales->im;
	return (res);
}
