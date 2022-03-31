/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 04:36:32 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/24 12:45:09 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	//float	jitter;

	//jitter = (ANIM_SCALE * 0.4 * cos(time / 100) * sin(time / 120));

	add[Z][Z] = sin(time / 1000);
	//printf("sin time %f \n", sin(time / 10000));
	/*0.2 + fabs(ANIM_SCALE * 25 * sin(time / 1000))
		+ jitter;*/
	//add[Z][X] = ANIM_SCALE * sin(time / 600) + jitter * 0.25;
	//add[Z][Y] = ANIM_SCALE * sin(time / 1200) + jitter * 0.25;
	v3listmul(add, map->points, map->length);
}
#endif

void	preprocess_map(t_map *map, t_mlx_i i)
{
	//scale_with_size_matrix(map, i.z_scale);
	//scale_with_global_z(map);
	v3listadd(map->points, (float [3]){-TRI_RES / 4, -512 / 4, 0}, map->length);
	scale_with_y_matrix(map, i.y_angle);
	scale_with_x_matrix(map, i.x_angle);
	v3listadd(map->points, (float [3]){(TRI_RES / 4)*2, (512 / 4) * 2, 0},
		map->length);
}
