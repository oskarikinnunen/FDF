/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <eino.oskari.kinnunen@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 04:36:32 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/04 22:57:02 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cpy_map(t_tri_map *src, t_tri_map *dst)
{
	int	i;

	i = 0;
	while (i < src->tri_count)
	{
		ft_memcpy(dst->tri_list[i][0], src->tri_list[i][0], sizeof(int [3]));
		ft_memcpy(dst->tri_list[i][1], src->tri_list[i][1], sizeof(int [3]));
		ft_memcpy(dst->tri_list[i][2], src->tri_list[i][2], sizeof(int [3]));
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
//t_map 
static void add_tri_map(t_tri_map *map, float add[3])
{
	int	i;

	i = 0;
	while (i < map->tri_count)
	{
		v3add(map->tri_list[i][0], add);
		v3add(map->tri_list[i][1], add);
		v3add(map->tri_list[i][2], add);
		i++;
	}
}

void	preprocess_map(t_tri_map *map, t_mlx_i i)
{
	//scale_with_size_matrix(map, i.z_scale);
	//scale_with_global_z(map);
	// ^Actually commented out
	add_tri_map(map, (float [3]){-TRI_RES / 4, -TRI_RES / 4, 0});
	scale_with_y_matrix(map, i.y_angle);
	scale_with_x_matrix(map, i.x_angle);
	add_tri_map(map, (float [3]){TRI_RES / 2, TRI_RES / 2, 0});
}
