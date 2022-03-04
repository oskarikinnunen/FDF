/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:38:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/04 19:08:48 by okinnune         ###   ########.fr       */
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

void	draw_line_img(int *i1, int *i2, char *adder, t_image_info i)
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
		*(adder + (i.bpp * local[X]) + (i.size_line * local[Y])) = 254;
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
