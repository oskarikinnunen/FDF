/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_drawing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:38:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/19 17:22:32 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <assert.h>

void	z_fill_sub_tri(int *tris[3], t_image_info img)
{
	t_bresenham	b[2];

	populate_bresenham(&(b[0]), tris[0], tris[1]);
	populate_bresenham(&(b[1]), tris[0], tris[2]);
	while (b[0].local[Y] != tris[1][Y])
	{
		z_draw_line(b[0].local, b[1].local, img);
		while (b[0].local[Y] == b[1].local[Y])
			step_bresenham(&(b[0]), tris[1]);
		while (b[1].local[Y] != b[0].local[Y])
			step_bresenham(&(b[1]), tris[2]);
	}
	z_draw_line(b[0].local, b[1].local, img);
}

void	z_fill_tri(int tris[3][3], t_image_info img)
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
	z_fill_sub_tri((int *[3]){(int *)&(sorted[0]),
		(int *)&(sorted[1]), (int *)&split}, img);
	z_fill_sub_tri((int *[3]){(int *)&(sorted[2]),
		(int *)&(sorted[1]), (int *)&split}, img);
	z_draw_line(sorted[0], sorted[2], img);
}

static void	z_draw_pixel(unsigned int offset, t_image_info img, int z)
{
	int	depth;

	depth = z >> 16;
	if (offset >= WSZ * (WSZ - IMAGE_Y))
		return ;
	if (*(unsigned int *)(img.z_buffer + offset) >> 16 < (unsigned int)depth)
		*(img.z_buffer + offset) = z;
}

void	z_draw_line(int *i1, int *i2, t_image_info img)
{
	t_bresenham		b;
	unsigned int	offset;

	populate_bresenham(&b, i1, i2);
	while (b.local[X] != i2[X] || b.local[Y] != i2[Y])
	{
		offset = b.local[X] + (b.local[Y] * (img.size_line / sizeof(int)));
		z_draw_pixel(offset, img, b.local[Z]);
		step_bresenham_x(&b, i2);
		offset = b.local[X] + (b.local[Y] * (img.size_line / sizeof(int)));
		z_draw_pixel(offset, img, b.local[Z]);
		step_bresenham_y(&b, i2);
	}
	offset = b.local[X] + (b.local[Y] * (img.size_line / sizeof(int)));
	z_draw_pixel(offset, img, b.local[Z]);
}
