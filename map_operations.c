/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 04:36:32 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/19 21:48:38 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	collect_square(float **v3, int i3[4][3], int width, int z)
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

void	cpy_map(t_map *src, t_map *dst)
{
	int	i;

	i = 0;
	while (i <= src->length)
	{
		ft_memcpy(dst->points[i], src->points[i], sizeof(float) * 3);
		i++;
	}
}

#ifdef EXTRA

void	animate_map(t_map *map, double time)
{
	static float	add[3][3] = {
	{1,	0, 0},
	{0, 1, 0},
	{0, 0, 1}
	};

	add[Z][Z] = fabs(ANIM_SCALE * 25 * sin(time / 1000));
	add[Z][X] = ANIM_SCALE * sin(time / 600);
	add[Z][Y] = ANIM_SCALE * sin(time / 1200);
	v3listmul(add, map->points, map->length);
}
#endif

void	preprocess_map(t_map *map, t_mlx_i i)
{
	scale_with_size_matrix(map);
	v3listadd(map->points, (float [3]){-WSZ / 4, -WSZ / 4, 0}, map->length);
	scale_with_y_matrix(map, i.y_angle);
	scale_with_x_matrix(map, i.x_angle);
	v3listadd(map->points, (float [3]){(WSZ / 4)*2, (WSZ / 4) * 2, 0},
		map->length);
}
