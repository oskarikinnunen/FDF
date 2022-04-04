/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <eino.oskari.kinnunen@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:38:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/04 19:15:02 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <assert.h>

/*	tris[0] 		=	lowest point
	tris[1]/tris[2] =	highest points	*/
void	fill_sub_tri(int *tris[3], char *addr, t_image_info img)
{
	t_bresenham	b[2];

	populate_bresenham(&(b[0]), tris[0], tris[1]);
	populate_bresenham(&(b[1]), tris[0], tris[2]);
	while (b[0].local[Y] != tris[1][Y])
	{
		draw_line_img(b[0].local, b[1].local, addr, img);
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
	fill_sub_tri((int *[3]){(int *)&(sorted[0]),
		(int *)&(sorted[1]), (int *)&split}, addr, img);
	fill_sub_tri((int *[3]){(int *)&(sorted[2]),
		(int *)&(sorted[1]), (int *)&split}, addr, img);
	draw_line_img(sorted[0], sorted[2], addr, img);
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
void	draw_line_img(int *i1, int *i2, char *addr, t_image_info img)
{
	t_bresenham		b;
	int				color;
	char			*pen;
	int				x_step;

	populate_bresenham(&b, i1, i2);
	x_step = img.bpp / 8;
	color = get_color(b.local[Z]);
	while (b.local[X] != i2[X] || b.local[Y] != i2[Y])
	{
		pen = addr + (b.local[X] * x_step) + b.local[Y] * img.size_line;
		*(unsigned int *)pen = color;
		step_bresenham_x(&b, i2);
		pen = addr + (b.local[X] * x_step) + b.local[Y] * img.size_line;
		*(unsigned int *)pen = color;
		step_bresenham_y(&b, i2);
	}
	pen = addr + (b.local[X] * x_step) + b.local[Y] * img.size_line;
	*(unsigned int *)pen = color;
}
