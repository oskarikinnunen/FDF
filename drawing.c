/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:38:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/18 15:08:44 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <assert.h>

/*static void	set_color(char *addr, char r, char g, char b)
{
	*(int *)addr = b + (g << 8) + (r << 16);
}*/

/*	tris[0] 		=	lowest point
	tris[1]/tris[2] =	highest points	*/
void	fill_topflat(int *tris[3], char *addr, t_image_info img)
{
	t_bresenham	b[2];

	pop_bresenham(&(b[0]), tris[0], tris[1]);
	pop_bresenham(&(b[1]), tris[0], tris[2]);
	while (b[0].local[Y] != tris[1][Y])
	{
		draw_line_img(b[0].local, b[1].local, addr, img);
		/*while (b[0].local[Y] == b[1].local[Y])
		{
			if (b[0].error * 2 <= b[0].diff[X] && b[0].local[Y] != tris[1][Y])
				b[0].error += (b[0].local[Y] += b[0].add[Y], b[0].diff[X]);
			if (b[0].error * 2 >= b[0].diff[Y] && b[0].local[X] != tris[1][X])
				b[0].error += (b[0].local[X] += b[0].add[X], b[0].diff[Y]);
		}
		while (b[1].local[Y] != b[0].local[Y])
		{
			if (b[1].error * 2 <= b[1].diff[X] && b[1].local[Y] != tris[2][Y])
				b[1].error += (b[1].local[Y] += b[1].add[Y], b[1].diff[X]);
			if (b[1].error * 2 >= b[1].diff[Y] && b[1].local[X] != tris[2][X])
				b[1].error += (b[1].local[X] += b[1].add[X], b[1].diff[Y]);
		}*/
		while (b[0].local[Y] == b[1].local[Y])
			step_bresenham(&(b[0]), tris[1]);
		while (b[1].local[Y] != b[0].local[Y])
			step_bresenham(&(b[1]), tris[2]);
	}
	draw_line_img(b[0].local, b[1].local, addr, img);
}

/*	tris[0] 		=	highest point
	tris[1]/tris[2] =	lowest points	*/
void	fill_bottomflat(int *tris[3], char *addr, t_image_info img)
{
	t_bresenham	b[2];

	pop_bresenham(&(b[0]), tris[0], tris[1]);
	pop_bresenham(&(b[1]), tris[0], tris[2]);
	while (b[0].local[Y] != tris[1][Y])
	{
		draw_line_img(b[0].local, b[1].local, addr, img);
		/*while (b[0].local[Y] == b[1].local[Y])
		{
			if (b[0].error * 2 <= b[0].diff[X] && b[0].local[Y] != tris[1][Y])
				b[0].error += (b[0].local[Y] += b[0].add[Y], b[0].diff[X]);
			if (b[0].error * 2 >= b[0].diff[Y] && b[0].local[X] != tris[1][X])
				b[0].error += (b[0].local[X] += b[0].add[X], b[0].diff[Y]);
		}
		while (b[1].local[Y] != b[0].local[Y])
		{
			if (b[1].error * 2 <= b[1].diff[X] && b[1].local[Y] != tris[2][Y])
				b[1].error += (b[1].local[Y] += b[1].add[Y], b[1].diff[X]);
			if (b[1].error * 2 >= b[1].diff[Y] && b[1].local[X] != tris[2][X])
				b[1].error += (b[1].local[X] += b[1].add[X], b[1].diff[Y]);
		}*/
		while (b[0].local[Y] == b[1].local[Y])
			step_bresenham(&(b[0]), tris[1]);
		while (b[1].local[Y] != b[0].local[Y])
			step_bresenham(&(b[1]), tris[2]);
	}
	draw_line_img(b[0].local, b[1].local, addr, img);
}

void	fill_tri(int tris[3][3], char *addr, t_image_info img)
{
	int		split[3];
	int		sorted[3][3];
	float	lerp;

	sort_tris(ft_memcpy(sorted, tris, sizeof(int [3][3])));
	lerp = (float)(sorted[1][Y] - sorted[2][Y])
		/ (float)(sorted[0][Y] - sorted[2][Y]);
	split[X] = sorted[2][X] + (lerp * (sorted[0][X] - sorted[2][X]));
	split[Y] = sorted[1][Y];
	split[Z] = sorted[1][Z];
	fill_topflat((int *[3]){(int *)&(sorted[0]),
		(int *)&(sorted[1]), (int *)&split}, addr, img);
	fill_bottomflat((int *[3]){(int *)&(sorted[2]),
		(int *)&(sorted[1]), (int *)&split}, addr, img);
	draw_line_img(sorted[0], sorted[2], addr, img);
}

void	draw_line_img(int *i1, int *i2, char *addr, t_image_info img)
{
	t_bresenham	b;
	int			color;
	char		*pen;
	int			x_step;

	pop_bresenham(&b, i1, i2);
	x_step = img.bpp / 8;
	color = b.local[Z] + (b.local[Z] << 8) + (0 << 16);
	while (b.local[X] != i2[X] || b.local[Y] != i2[Y])
	{
		pen = addr + (b.local[X] * x_step) + b.local[Y] * img.size_line;
		*(int *)pen = color;
		if (b.error * 2 <= b.diff[X] && b.local[Y] != i2[Y])
			b.error += (b.local[Y] += b.add[Y], b.diff[X]);
		//step_bresenham_x(&b, i2);
		pen = addr + (b.local[X] * x_step) + b.local[Y] * img.size_line;
		*(int *)pen = color;
		if (b.error * 2 >= b.diff[Y] && b.local[X] != i2[X])
			b.error += (b.local[X] += b.add[X], b.diff[Y]);
		//step_bresenham_y(&b, i2);
	}
	pen = addr + (b.local[X] * x_step) + b.local[Y] * img.size_line;
	*(int *)pen = color;
}
