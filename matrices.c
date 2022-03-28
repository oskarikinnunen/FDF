/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 04:53:43 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/24 12:50:34 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_with_size_matrix(t_map *map)
{
	static float	scale[3][3] = {
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1}
	};
	float			scale_by;

	scale_by = ft_max(map->width, map->length / map->width);
	scale_by = (WSZ / scale_by) * 0.55;
	scale[X][X] = scale_by;
	scale[Y][Y] = scale_by;
	scale[Z][Z] = scale_by * Z_SCALE;
	v3listmul(scale, map->points, map->length);
}

void	scale_with_y_matrix(t_map *map, double angle)
{
	static float	iso[3][3] = {
	{1, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
	};

	angle = angle * PI / 180;
	angle = asin(ft_clampf(tan(angle), -1.0, 1.0));
	iso[Y][Y] = cos(angle);
	iso[Y][Z] = sin(angle);
	iso[Z][Y] = -sin(angle);
	iso[Z][Z] = cos(angle);
	v3listmul(iso, map->points, map->length);
}

/* Alternative pivot (z):
	iso[X][X] = cos(angle);
	iso[X][Z] = -sin(angle);
	iso[Z][X] = sin(angle);
	iso[Z][Z] = cos(angle)
*/
void	scale_with_x_matrix(t_map *map, double angle)
{
	static float	iso[3][3] = {
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1}
	};

	angle = angle * PI / 180;
	iso[X][X] = cos(angle);
	iso[X][Z] = -sin(angle);
	iso[Z][X] = sin(angle);
	iso[Z][Z] = cos(angle);
	/*iso[X][X] = cos(angle);
	iso[X][Y] = -sin(angle);
	iso[Z][X] = sin(angle);
	iso[Z][Y] = cos(angle);*/
	v3listmul(iso, map->points, map->length);
}
