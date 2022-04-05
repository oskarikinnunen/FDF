/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:38:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/06 00:34:04 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <assert.h>

/*	tris[0] 		=	lowest point
	tris[1]/tris[2] =	highest points	*/
void	fill_sub_tri(int *tris[3], t_image_info img)
{
	t_bresenham	b[2];

	populate_bresenham(&(b[0]), tris[0], tris[1]);
	populate_bresenham(&(b[1]), tris[0], tris[2]);
	while (b[0].local[Y] != tris[1][Y])
	{
		draw_line_img(b[0].local, b[1].local, img);
		while (b[0].local[Y] == b[1].local[Y])
			step_bresenham(&(b[0]), tris[1]);
		while (b[1].local[Y] != b[0].local[Y])
			step_bresenham(&(b[1]), tris[2]);
	}
	draw_line_img(b[0].local, b[1].local, img);
}

void	fill_tri(int tris[3][3], t_image_info img)
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
	fill_sub_tri((int *[3]){(int *)&(sorted[0]),
		(int *)&(sorted[1]), (int *)&split}, img);
	fill_sub_tri((int *[3]){(int *)&(sorted[2]),
		(int *)&(sorted[1]), (int *)&split}, img);
	draw_line_img(sorted[0], sorted[2], img);
}

static int get_color(int z)
{
	int	r;
	int	g;
	int	b;
	int	r_range;
	int	g_range;
	int	b_range;
	int color;

	r_range = 100;
	b_range = 100;
	g_range = 100;
	r = ft_max(0, r_range - ft_abs(z - 0));
	g = ft_max(0, g_range - ft_abs(z - 127));
	b = ft_max(0, b_range - ft_abs(z - 255));
	color = b + (g << 8) + (r << 16);
	return (color);
}

//TODO: Make this better!!
//step_bresenham_x(&b, i2);
//step_bresenham_y(&b, i2);
static void check_z_pass(int offset, t_image_info img, int z)
{
	int	depth;
	int	color;

	color = z & 0xFFFF;
	depth = z >> 16;
	*(unsigned int *)(img.addr + (offset * sizeof(int))) = get_color(color);
	/*if (*(unsigned int *)(img.z_buffer + offset) < (unsigned int)depth)
	{
		*(img.z_buffer + offset) = depth;
		
	}*/
}

void	draw_line_img(int *i1, int *i2, t_image_info img)
{
	t_bresenham		b;
	int				color;
	int				offset;

	populate_bresenham(&b, i1, i2);
	while (b.local[X] != i2[X] || b.local[Y] != i2[Y])
	{
		offset = b.local[X] + (b.local[Y] * (img.size_line / sizeof(int)));
		check_z_pass(offset, img, b.local[Z]);
		step_bresenham_x(&b, i2);
		offset = b.local[X] + (b.local[Y] * (img.size_line / sizeof(int)));
		check_z_pass(offset, img, b.local[Z]);
		step_bresenham_y(&b, i2);
	}
	offset = b.local[X] + (b.local[Y] * (img.size_line / sizeof(int)));
	check_z_pass(offset, img, b.local[Z]);
}
