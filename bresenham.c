/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:09:50 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/16 12:00:18 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	step_bresenham_x(t_brasenham *b, int target[3])
{
	if (b->error * 2 <= b->diff[X] && b->local[Y] != target[Y])
	{
		b->error += b->diff[X];
		b->local[Y] += b->add[Y];
	}
}

void	step_bresenham_y(t_brasenham *b, int target[3])
{
	if (b->error * 2 >= b->diff[Y] && b->local[X] != target[X])
	{
		b->error += b->diff[Y];
		b->local[X] += b->add[X];
	}
}

void	step_bresenham(t_brasenham *b, int target[3])
{
	if (b->error * 2 <= b->diff[X] && b->local[Y] != target[Y])
	{
		b->error += b->diff[X];
		b->local[Y] += b->add[Y];
	}
	if (b->error * 2 >= b->diff[Y] && b->local[X] != target[X])
	{
		b->error += b->diff[Y];
		b->local[X] += b->add[X];
	}
}

void	pop_brasenham(t_brasenham *b, int *from, int *to)
{
	ft_memcpy(b->local, from, sizeof(int) * 3);
	b->diff[X] = ft_abs(b->local[X] - to[X]);
	b->diff[Y] = -ft_abs(b->local[Y] - to[Y]);
	b->add[X] = 1 - ((b->local[X] > to[X]) * 2);
	b->add[Y] = 1 - ((b->local[Y] > to[Y]) * 2);
	b->error = b->diff[X] + b->diff[Y];
}
