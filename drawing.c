/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:38:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/15 13:12:44 by okinnune         ###   ########.fr       */
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

//INT[3]!!! top, bot1, bot2
void	fill_bottom_tri(int *tris[3], char *adder,
	t_image_info i)
{
	int			sort[2][3];
	t_brasenham	b[2];
	int			scan;

	ft_memcpy(sort[0], tris[2], sizeof(int) * 3);
	ft_memcpy(sort[1], tris[1], sizeof(int) * 3);
	if (tris[1][X] < tris[2][X])
	{
		ft_memcpy(sort[1], tris[2], sizeof(int) * 3);
		ft_memcpy(sort[0], tris[1], sizeof(int) * 3);
	}
	pop_brasenham(&(b[0]), tris[0], sort[0]);
	pop_brasenham(&(b[1]), tris[0], sort[1]);
	while (b[0].local[Y] != sort[0][Y] && sort[0][Y] > 0)
	{
		draw_line_img(b[0].local, (int [3]){b[1].local[X] + 2, b[0].local[Y], b[0].local[Z]}, adder, i);
		while (b[0].local[Y] == b[1].local[Y])
			step_bresenham(&(b[0]), sort[0]);
		while (b[1].local[Y] != b[0].local[Y] && b[1].local[Y] != sort[1][Y]) //dum
			step_bresenham(&(b[1]), sort[1]);
		draw_line_img(b[0].local, b[1].local, adder, i);
	}
	draw_line_img(b[0].local, b[1].local, adder, i);
}

//bot, top1, tris[2]
void	fill_top_tri(int *tris[3], char *adder, t_image_info i)
{
	int			sort[2][3];
	t_brasenham	b[2];

	ft_memcpy(sort[0], tris[2], sizeof(int) * 3);
	ft_memcpy(sort[1], tris[1], sizeof(int) * 3);
	if (tris[1][X] < tris[2][X])
	{
		ft_memcpy(sort[1], tris[2], sizeof(int) * 3);
		ft_memcpy(sort[0], tris[1], sizeof(int) * 3);
	}
	pop_brasenham(&(b[0]), tris[0], sort[0]);
	pop_brasenham(&(b[1]), tris[0], sort[1]);
	while (b[0].local[Y] != sort[0][Y] && sort[0][Y] > 0)
	{
		draw_line_img(b[0].local, (int [3]){b[1].local[X] + 2, b[1].local[Y], b[1].local[Z]}, adder, i);
		while (b[0].local[Y] == b[1].local[Y])
			step_bresenham(&(b[0]), sort[0]);
		while (b[1].local[Y] != b[0].local[Y] && b[1].local[Y] != sort[1][Y])
			step_bresenham(&(b[1]), sort[1]);
		draw_line_img((int [3]){b[0].local[X], b[0].local[Y] + 2, b[0].local[Z]}
					, (int [3]){b[1].local[X], b[0].local[Y] + 2, b[0].local[Z]}, adder, i);
	}
	draw_line_img(b[0].local, b[1].local, adder, i);
}

void	fill_tri(int tris[3][3], int vert_z, char *adder, t_image_info i)
{
	int		split[3];
	int		sorted[3][3];
	float	lerp;

	ft_memcpy(sorted, tris, sizeof(int [3][3]));
	sort_tris(sorted);
	lerp = (float)(sorted[1][Y] - sorted[2][Y])
		/ (float)(sorted[0][Y] - sorted[2][Y]);
	split[X] = sorted[2][X] + (lerp * (sorted[0][X] - sorted[2][X]));
	split[Y] = sorted[2][Y] + (lerp * (sorted[0][Y] - sorted[2][Y]));
	split[Z] = vert_z;
	sorted[0][Z] = vert_z;
	sorted[1][Z] = vert_z;
	sorted[2][Z] = vert_z;
	fill_bottom_tri((int *[3]){&(sorted[0]), &(sorted[1]), &split}, adder, i);
	fill_top_tri((int *[3]){&(sorted[2]), &(sorted[1]), &split}, adder, i);
	//draw_line_img(sorted[0], sorted[2], adder, i);
}

void	draw_line_img(int *i1, int *i2, char *adder, t_image_info i)
{
	t_brasenham	b;

	ft_memcpy(b.local, i1, sizeof(int) * 3);
	b.diff[X] = ft_abs(b.local[X] - i2[X]);
	b.diff[Y] = -ft_abs(b.local[Y] - i2[Y]);
	b.add[X] = 1 - ((b.local[X] > i2[X]) * 2);
	b.add[Y] = 1 - ((b.local[Y] > i2[Y]) * 2);
	b.error = b.diff[X] + b.diff[Y];
	while ((b.local[X] != i2[X] || b.local[Y] != i2[Y]))
	{
		*(int *)(adder + (b.local[X] * (i.bpp / 8))
				+ (i.size_line * b.local[Y])) = color(120, (int)(b.local[Z] * 0.5f), (int)(b.local[Z] * 0.5f));
		if (b.error * 2 >= b.diff[Y] && b.local[X] != i2[X])
		{
			b.error += b.diff[Y];
			b.local[X] += b.add[X];
		}
		if (b.error * 2 <= b.diff[X] && b.local[Y] != i2[Y])
		{
			b.error += b.diff[X];
			b.local[Y] += b.add[Y];
		}
	}
}
