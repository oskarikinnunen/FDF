/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:38:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/09 23:57:14 by okinnune         ###   ########.fr       */
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

void	sort_tris(int tris[4][3])
{
	int	s_x;
	int	s_j;
	int	temp[3];

	while (s_x < 3)
	{
		while (s_j < 3 - s_x - 1)
		{
			if (tris[s_j][Y] > tris[s_j + 1][Y])
			{
				ft_memcpy(temp, tris[s_j], sizeof(int) * 3);
				ft_memcpy(tris[s_j], tris[s_j + 1], sizeof(int) * 3);
				ft_memcpy(tris[s_j + 1], temp, sizeof(int) * 3);
			}
			s_j++;
		}
		s_x++;
	}
	//TEST!
}

void	fill_bottom_tri(int *top, int *bot1, int *bot2, char *adder, t_image_info i)
{
	int		sort[2][2];
	float	slope1;
	float	slope2;
	float	xs[2];
	int		scan;

	ft_memcpy(sort[0], bot2, sizeof(int) * 2);
	ft_memcpy(sort[1], bot1, sizeof(int) * 2);
	if (bot1[X] < bot2[X])
	{
		ft_memcpy(sort[1], bot2, sizeof(int) * 2);
		ft_memcpy(sort[0], bot1, sizeof(int) * 2);
	}
	slope1 = (sort[0][X] - top[X]) / (sort[0][Y] - top[Y]);
	slope2 = (sort[1][X] - top[X]) / (sort[1][Y] - top[Y]);
	scan = top[Y];
	xs[0] = top[X];
	xs[1] = top[X];
	while (scan < (int)(bot2[Y]))
	{
		int temp[3];
		int temp2[3];
		temp[X] = xs[0];
		temp[Y] = scan;
		temp2[X] = xs[1];
		temp2[Y] = scan;
		draw_line_img(temp, temp2, adder, i, INT_MAX);
		xs[0] += slope1;
		xs[1] += slope2;
		scan++;
	}
}

void	fill_tri(int tris[4][3], char *adder, t_image_info i)
{
	int	split[3];
	sort_tris(tris);
	/*for (int x = 0; x < 3; x++)
	{
		printf("TRIS %i X%i Y%i Z%i\n", x, tris[x][X], tris[x][Y], tris[x][Z]);
	}*/
	split[X] = tris[0][X] + (tris[1][Y] - tris[0][Y]) / (tris[2][Y] - tris[0][Y]) * (tris[2][X] - tris[0][X]);
	split[Y] = tris[1][Y];
	split[Z] = 0;

	fill_bottom_tri(tris[0], tris[1], split, adder, i);
	//draw_line_img(tris[0], split, adder, i, INT_MAX);


	//exit(0);
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
		*(int *)(adder + (local[X] * (i.bpp / 8)) + (i.size_line * local[Y])) = clr; //Have no idea why this needs to be hardcoded 4 instead of i.bpp...
		//Linememory.add(local);
		if (error * 2 >= diff[Y] && local[X] != i2[X])
		{
			error += diff[Y];
			local[X] += add[X];
		}
		if (error * 2 <= diff[X] && local[Y] != i2[Y])
		{
			error += diff[X];
			local[Y] += add[Y];
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
	printf("Initial error %i \n", error);
	while ((local[X] != i2[X] || local[Y] != i2[Y]))
	{
		mlx_pixel_put(i.mlx, i.win, local[X], local[Y], c);
		printf("error step %i \n", error);
		if (error * 2 >= diff[Y] && local[X] != i2[X])
		{
			error += diff[Y];
			local[X] += add[X];
		}
		if (error * 2 <= diff[X] && local[Y] != i2[Y])
		{
			error += diff[X];
			local[Y] += add[Y];
		}
	}
	exit(0);
}
