/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_drawing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:38:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/25 08:09:56 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <assert.h>


static void	get_min_i3(int result[2][3], int *i1, int *i2)
{
	result[0][X] = ft_min(i1[X], i2[X]);
	result[0][Y] = ft_min(i1[Y], i2[Y]);
	result[0][Z] = ft_min(i1[Z], i2[Z]);
	result[1][X] = ft_max(i1[X], i2[X]);
	result[1][Y] = ft_max(i1[Y], i2[Y]);
	result[1][Z] = ft_max(i1[Z], i2[Z]);
}
/*	tris[0] 		=	lowest point
	tris[1]/tris[2] =	highest points	*/
static void	fill_z_topflat(int *tris[3], char *addr, t_image_info img, int color)
{
	t_bresenham	b[2];
	double		z_lerp;

	populate_bresenham(&(b[0]), tris[0], tris[1]);
	populate_bresenham(&(b[1]), tris[0], tris[2]);
	//printf("fill Origin z %i Target z %i \n", tris[0][Z], tris[1][Z]);
	while (b[0].local[Y] != tris[1][Y])
	{
		z_lerp = (double)(b[0].local[Y] - tris[0][Y]) / (double)(tris[1][Y] - tris[0][Y]);
		b[0].local[Z] = tris[1][Z] + ((double)(tris[0][Z] - tris[1][Z]) * z_lerp);
		b[1].local[Z] = tris[2][Z] + ((double)(tris[0][Z] - tris[2][Z]) * z_lerp);
		//printf("fill z_values 0 %i \n", z_values[0]);
		draw_z_line_img(b[0].local, b[1].local, img, color);
		while (b[0].local[Y] == b[1].local[Y])
			step_bresenham(&(b[0]), tris[1]);
		while (b[1].local[Y] != b[0].local[Y])
			step_bresenham(&(b[1]), tris[2]);
	}
	draw_z_line_img(b[0].local, b[1].local, img, color);
}

/*	tris[0] 		=	highest point
	tris[1]/tris[2] =	lowest points	*/
static void	fill_z_bottomflat(int *tris[3], char *addr, t_image_info img, int color)
{
	t_bresenham	b[2];
	float		z_lerp;

	populate_bresenham(&(b[0]), tris[0], tris[1]);
	populate_bresenham(&(b[1]), tris[0], tris[2]);
	while (b[0].local[Y] != tris[1][Y])
	{
		z_lerp = (double)(b[0].local[Y] - tris[0][Y]) / (double)(tris[1][Y] - tris[0][Y]);
		b[0].local[Z] = tris[0][Z] + ((double)(tris[1][Z] - tris[0][Z]) * z_lerp);
		b[1].local[Z] = tris[0][Z] + ((double)(tris[2][Z] - tris[0][Z]) * z_lerp);
		draw_z_line_img(b[0].local, b[1].local, img, color);
		while (b[0].local[Y] == b[1].local[Y])
			step_bresenham(&(b[0]), tris[1]);
		while (b[1].local[Y] != b[0].local[Y])
			step_bresenham(&(b[1]), tris[2]);
	}
	draw_z_line_img(b[0].local, b[1].local, img, color);
}

void	fill_z_tri(int tris[3][3], char *addr, t_image_info img, int color)
{
	int		split[3];
	int		sorted[3][3];
	float	lerp;

	sort_tris(ft_memcpy(sorted, tris, sizeof(int [3][3])));
	lerp = (float)(sorted[1][Y] - sorted[2][Y])
		/ (float)(sorted[0][Y] - sorted[2][Y]);
	split[X] = sorted[2][X] + (lerp * (sorted[0][X] - sorted[2][X]));
	split[Y] = sorted[1][Y];
	split[Z] = sorted[2][Z] + (lerp * (sorted[0][Z] - sorted[2][Z]));
	fill_z_topflat((int *[3]){(int *)&(sorted[0]),
		(int *)&(sorted[1]), (int *)&split}, addr, img, color);
	/*fill_z_bottomflat((int *[3]){(int *)&(sorted[2]),
		(int *)&(sorted[1]), (int *)&split}, addr, img, color);*/
	//draw_z_line_img(sorted[0], sorted[2], img);
	//exit(0);
}

void	draw_z_line_img(int *i1, int *i2, t_image_info img, int color)
{
	t_bresenham		b;
	signed int	z_height;
	signed int	*z_pen;
	int				x_step;
	int				sorted[2][3];
	double			z_lerp;

	populate_bresenham(&b, i1, i2);
	//x_step = img.bpp / 8;
	z_pen = img.depthlayer;
	get_min_i3(sorted, i1, i2);
	/*printf("min z %i max z %i \n", sorted[0][Z], sorted[1][Z]);
	printf("1 z %i 2 z %i \n", i1[Z], i2[Z]);*/
	while (b.local[X] != i2[X] || b.local[Y] != i2[Y])
	{
		z_pen = img.depthlayer + (b.local[X]) + (b.local[Y] * (WSZ));
		z_lerp = (double)(b.local[X] - sorted[0][X]) / (double)(sorted[1][X] - sorted[0][X]);
		z_height = (double)(sorted[0][Z] + ((double)(sorted[1][Z] - sorted[0][Z]) * z_lerp));
		//printf("Offset pixel %li \n", z_pen - img.depthlayer);
		//printf("lerp %f z_height %i \n", z_lerp, z_height);
		//printf("read z_height %i \n", (*z_pen) >> 8);
		if ((*z_pen >> 8) <= z_height)
			*z_pen = (color & Z_CLRMASK) + (z_height >> 8);
		step_bresenham_x(&b, i2);
		z_pen = img.depthlayer + (b.local[X]) + (b.local[Y] * (WSZ));
		if ((*z_pen >> 8) <= z_height)
			*z_pen = (color & Z_CLRMASK) + (z_height >> 8);
		step_bresenham_y(&b, i2);
		z_pen = img.depthlayer + (b.local[X]) + (b.local[Y] * (WSZ));
		//printf("original z = %i compare to %i \n", *z_pen >> 8, z_height);
		if ((*z_pen >> 8) <= z_height)
			*z_pen = (color & Z_CLRMASK) + (z_height >> 8);
	}
	/*z_pen = img.depthlayer + (b.local[X] * sizeof(int)) + b.local[Y] * img.size_line;
		if ((*z_pen & Z_HGHTMASK) < z_height)
			*z_pen = (color & Z_CLRMASK) + (z_height << 8);*/
}

/*void	draw_line_z_pass(int *i1, int *i2, char *addr, t_image_info img)
{
	t_bresenham	b;
	int			color;
	char		*pen;
	int			x_step;

	populate_bresenham(&b, i1, i2);
	x_step = img.bpp / 8;
	color = b.local[Z] + (b.local[Z] << 8) + (0 << 16);
	while (b.local[X] != i2[X] || b.local[Y] != i2[Y])
	{
		pen = addr + (b.local[X] * x_step) + b.local[Y] * img.size_line;
		*(int *)pen = color;
		if (b.error * 2 <= b.diff[X] && b.local[Y] != i2[Y])
			b.error += (b.local[Y] += b.add[Y], b.diff[X]);
		pen = addr + (b.local[X] * x_step) + b.local[Y] * img.size_line;
		*(int *)pen = color;
		if (b.error * 2 >= b.diff[Y] && b.local[X] != i2[X])
			b.error += (b.local[X] += b.add[X], b.diff[Y]);
	}
	pen = addr + (b.local[X] * x_step) + b.local[Y] * img.size_line;
	*(int *)pen = color;
}*/