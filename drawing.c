/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:38:17 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/16 15:58:13 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <assert.h>

int	color(char r, char g, char b)
{
	int	c;

	c = 0;
	((char *)&c)[0] = b;
	((char *)&c)[1] = g;
	((char *)&c)[2] = r;
	return (c);
}

int	set_color(int *i, char r, char g, char b)
{
	((char *)i)[0] = b;
	((char *)i)[1] = g;
	((char *)i)[2] = r;
}

//INT[3]!!! top, bot1, bot2
void	fill_bottom_tri(int *tris[3], char *adder,
	t_image_info i)
{
	t_brasenham	b[2];

	pop_brasenham(&(b[0]), tris[0], tris[1]);
	pop_brasenham(&(b[1]), tris[0], tris[2]);
	while (b[0].local[Y] != tris[1][Y] && tris[1][Y] > 0)
	{
		draw_line_img(b[0].local, b[1].local, adder, i);
		while (b[0].local[Y] == b[1].local[Y])
			step_bresenham(&(b[0]), tris[1]);
		while (b[1].local[Y] != b[0].local[Y] && b[1].local[Y] != tris[2][Y]) //dum
			step_bresenham(&(b[1]), tris[2]);
	}
	draw_line_img(b[0].local, b[1].local, adder, i);
}

//bot, top1, tris[2]
void	fill_top_tri(int *tris[3], char *adder, t_image_info i)
{
	t_brasenham	b[2];

	pop_brasenham(&(b[0]), tris[0], tris[1]);
	pop_brasenham(&(b[1]), tris[0], tris[2]);
	while (b[0].local[Y] != tris[1][Y] && tris[1][Y] > 0)
	{
		draw_line_img(b[0].local, b[1].local, adder, i);
		while (b[0].local[Y] == b[1].local[Y])
			step_bresenham(&(b[0]), tris[1]);
		while (b[1].local[Y] != b[0].local[Y] && b[1].local[Y] != tris[2][Y])
			step_bresenham(&(b[1]), tris[2]);
	}
	draw_line_img(b[0].local, b[1].local, adder, i);
}

void	fill_tri(int tris[3][3], int vert_z, char *adder, t_image_info i)
{
	int		split[3];
	int		sorted[3][3];
	float	lerp;
	//int		lerp_i;

	ft_memcpy(sorted, tris, sizeof(int [3][3]));
	sort_tris(sorted);
	lerp = (float)(sorted[1][Y] - sorted[2][Y])
		/ (float)(sorted[0][Y] - sorted[2][Y]);
	split[X] = sorted[2][X] + (lerp * (sorted[0][X] - sorted[2][X]));
	split[Y] = sorted[1][Y];
	split[Z] = vert_z;
	sorted[0][Z] = vert_z;
	sorted[1][Z] = vert_z;
	sorted[2][Z] = vert_z;
	fill_bottom_tri((int *[3]){&(sorted[0]), &(sorted[1]), &split}, adder, i);
	fill_top_tri((int *[3]){&(sorted[2]), &(sorted[1]), &split}, adder, i);
	draw_line_img(sorted[0], sorted[2], adder, i);
}

void	draw_line_img(int *i1, int *i2, char *adder, t_image_info i)
{
	t_brasenham	b;
	char		z_color;

	pop_brasenham(&b, i1, i2);
	z_color = ((char *)&(b.local[Z]))[0];
	//z_color = b.local[Z];
	while (b.local[X] != i2[X] || b.local[Y] != i2[Y])
	{
		//printf("about to set color X %i Y %i \n", b.local[X], b.local[Y]);
		set_color((int *)(adder + (b.local[X] * (i.bpp / 8))
				+ (i.size_line * b.local[Y])),
				120, z_color, z_color);
		step_bresenham_x(&b, i2);
		//printf("z value for %i %i is %i \n", b.local[X], b.local[Y], i.z_values[b.local[X] + (b.local[Y] * (i.size_line / 4))]);
		set_color((int *)(adder + (b.local[X] * (i.bpp / 8))
				+ (i.size_line * b.local[Y])),
				120, z_color, z_color);
		step_bresenham_y(&b, i2);
	}
	set_color((int *)(adder + (b.local[X] * (i.bpp / 8))
				+ (i.size_line * b.local[Y])),
				120, z_color, z_color);
}
