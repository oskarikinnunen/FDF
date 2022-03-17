/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 04:36:32 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/17 07:38:14 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	collect_square(float **v3, int i3[4][3], int width, int z)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		i3[i][X] = v3[((i >= 2) * width) + !((i + 1) % 2)][X];
		i3[i][X] = ft_clamp(i3[i][X], 0, WSZ);
		i3[i][Y] = v3[((i >= 2) * width) + !((i + 1) % 2)][Y];
		i3[i][Y] = ft_clamp(i3[i][Y], 0, WSZ);
		i3[i][Z] = z;
		i++;
	}
}

void	map_cpy(t_map *src, t_map *dst)
{
	int	i;

	i = 0;
	while (i <= src->length)
	{
		ft_memcpy(dst->points[i], src->points[i], sizeof(float) * 3);
		i++;
	}
}

void	map_animate(t_map *map, double time)
{
	static float	add[3][3] = {
	{1,	0, 0},
	{0, 1, 0},
	{0, 0, 1}
	};

	add[Z][Z] = 1 * sin(time / 1000);
	v3listmul(add, map->points, map->length);
}

void	map_preprocess(t_map *map, t_mlx_i i)
{
	float	add[3];
	float	matrix[3][3];

	add[X] = WSZ / 4;
	add[Y] = WSZ / 4;
	add[Z] = 20;
	setmatrix_scale(matrix);
	v3listmul(matrix, map->points, map->length);
	setmatrix_iso_y(matrix, i.x_angle);
	v3listmul(matrix, map->points, map->length);
	setmatrix_iso_x(matrix, i.y_angle);
	v3listmul(matrix, map->points, map->length);
	v3listadd(map->points, add, map->length);
}

void	map_to_image(char *addr, t_map map, t_image_info img)
{
	int		cur;
	int		v3_integers[4][3];
	int		vert_z;

	cur = 0;
	while ((cur + map.width + 1) <= map.length)
	{
		vert_z = (char)img.z_values[cur] + (char)img.z_values[cur + 1]
			+ (char)img.z_values[cur + map.width]
			+ (char)img.z_values[cur + map.width + 1];
		vert_z = ft_clamp(vert_z / 4, -128, 127) + 128;
		//move z buff to "real" coordinate
		collect_square(&(map.points[cur]), v3_integers, map.width, vert_z);
		fill_tri(v3_integers, addr, img);
		fill_tri(&(v3_integers[1]), addr, img);
		draw_line_img(v3_integers[0], v3_integers[1], addr, img);
		draw_line_img(v3_integers[1], v3_integers[2], addr, img);
		draw_line_img(v3_integers[0], v3_integers[2], addr, img);
		cur++;
		cur += ((cur + 1) % map.width == 0);
	}
}
