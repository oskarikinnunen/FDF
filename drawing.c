/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:38:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/08 20:47:41 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <assert.h>

int	color(char r, char g, char b)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (i < 8)
	{
		c ^= (((1 << i & r) != 0)) << (i + 16);
		c ^= (((1 << i & g) != 0)) << (i + 8);
		c ^= (((1 << i & b) != 0)) << i;
		i++;
	}
	return (c);
}

void	draw_rect_img(int *i1, int *i2, char *adder, t_image_info i)
{
	int	topright[2];
	int	botmleft[2];

	topright[X] = i2[X];
	topright[Y] = i1[Y];
	botmleft[X] = i2[Y];
	botmleft[Y] = i1[X];
	draw_line_img(i1, topright, adder, i, INT_MAX);
	draw_line_img(i1, botmleft, adder, i, INT_MAX);
	draw_line_img(i2, topright, adder, i, INT_MAX);
	draw_line_img(i2, botmleft, adder, i, INT_MAX);
}

void	draw_line_img(int *i1, int *i2, char *adder, t_image_info i, int clr)
{
	int		diff[3];
	int		add[3];
	int		local[3];
	int		error;

	ft_memcpy(local, i1, sizeof(int) * 3);
	diff[X] = ft_abs(local[X] - i2[X]);
	diff[Y] = -ft_abs(local[Y] - i2[Y]);
	add[X] = 1 - ((local[X] > i2[X]) * 2);
	add[Y] = 1 - ((local[Y] > i2[Y]) * 2);
	error = diff[X] + diff[Y];
	while ((local[X] != i2[X] || local[Y] != i2[Y]))
	{
		//mlx_pixel_put(i.mlx, i.win, local[X], local[Y], c);
		//printf("drawing %lu local X %i local Y %i\n", adder + (local[X] * (i.bpp / 8)) + (i.size_line * local[Y]), local[X], local[Y]);
		*(int *)(adder + (local[X] * (i.bpp / 8)) + (i.size_line * local[Y])) = clr; //Have no idea why this needs to be hardcoded 4 instead of i.bpp...
		if (error * 2 >= diff[Y])
		{
			error += (local[X] != i2[X]) * diff[Y];
			local[X] += (local[X] != i2[X]) * add[X];
		}
		if (error * 2 <= diff[X])
		{
			error += (local[Y] != i2[Y]) * diff[X];
			local[Y] += (local[Y] != i2[Y]) * add[Y];
		}
	}
}

void	draw_line(int *i1, int *i2, t_mlx_i i, int c)
{
	int		diff[3];
	int		add[3];
	int		local[3];
	int		error;

	ft_memcpy(local, i1, sizeof(int) * 3);
	diff[X] = ft_abs(local[X] - i2[X]);
	diff[Y] = -ft_abs(local[Y] - i2[Y]);
	add[X] = 1 - ((local[X] > i2[X]) * 2);
	add[Y] = 1 - ((local[Y] > i2[Y]) * 2);
	error = diff[X] + diff[Y];
	while ((local[X] != i2[X] || local[Y] != i2[Y]))
	{
		mlx_pixel_put(i.mlx, i.win, local[X], local[Y], c);
		if (error * 2 >= diff[Y])
		{
			error += (local[X] != i2[X]) * diff[Y];
			local[X] += (local[X] != i2[X]) * add[X];
		}
		if (error * 2 <= diff[X])
		{
			error += (local[Y] != i2[Y]) * diff[X];
			local[Y] += (local[Y] != i2[Y]) * add[Y];
		}
	}
}
