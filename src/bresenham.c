/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:09:50 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/21 14:37:39 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	step_bresenham_x(t_bresenham *b, int target[3])
{
	if (b->error * 2 < b->diff[X] && b->local[Y] != target[Y])
	{
		b->local[Y] += b->add[Y];
		b->error += b->diff[X];
	}
}

void	step_bresenham_y(t_bresenham *b, int target[3])
{
	if (b->error * 2 > b->diff[Y] && b->local[X] != target[X])
	{
		b->local[X] += b->add[X];
		b->error += b->diff[Y];
	}
}

void	step_bresenham(t_bresenham *b, int target[3])
{
	step_bresenham_x(b, target);
	step_bresenham_y(b, target);
}

void	populate_bresenham(t_bresenham *b, int *from, int *to)
{
	ft_memcpy(b->local, from, sizeof(int) * 3);
	b->diff[X] = ft_abs(b->local[X] - to[X]);
	b->diff[Y] = -ft_abs(b->local[Y] - to[Y]);
	b->add[X] = 1 - ((b->local[X] > to[X]) * 2);
	b->add[Y] = 1 - ((b->local[Y] > to[Y]) * 2);
	b->error = b->diff[X] + b->diff[Y];
}
