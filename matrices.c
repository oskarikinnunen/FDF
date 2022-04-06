/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <eino.oskari.kinnunen@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 04:53:43 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/06 18:03:56 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//TODO: no pointer needed?

void mul_tri_map(float matrix[3][3], t_tri_map map)
{
	int	i;

	i = 0;
	while (i < map.tri_count)
	{
		v3mul(matrix, map.tri_list[i][0]);
		v3mul(matrix, map.tri_list[i][1]);
		v3mul(matrix, map.tri_list[i][2]);
		i++;
	}
}

void	scale_with_size_matrix(t_tri_map map, double z_scale)
{
	static float	scale[3][3] = {
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1}
	};
	float			scale_by;

	scale_by = ft_max(map.dimensions[X] - 1, map.dimensions[Y] - 1);
	scale_by = (WSZ / scale_by) * 0.80;
	scale[X][X] = scale_by;
	scale[Y][Y] = scale_by;
	scale[Z][Z] = z_scale;
	mul_tri_map(scale, map);
	//v3listmul(scale, map->points, map->length);
}

void	scale_with_y_matrix(t_tri_map map, double angle)
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
	mul_tri_map(iso, map);
	//v3listmul(iso, map->points, map->length);
}

/* Alternative pivot (z):
	iso[X][X] = cos(angle);
	iso[X][Z] = -sin(angle);
	iso[Z][X] = sin(angle);
	iso[Z][Z] = cos(angle)
*/
void	scale_with_x_matrix(t_tri_map map, double angle)
{
	static float	iso[3][3] = {
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1}
	};

	angle = angle * PI / 180;
	iso[X][X] = cos(angle);
	iso[X][Y] = -sin(angle);
	iso[Y][X] = sin(angle);
	iso[Y][Y] = cos(angle);
	//iso[Y][Y] = -sin(angle);
	//iso[X][Z] = -sin(angle);
	//iso[Z][X] = sin(angle);
	//iso[Z][Y] = cos(angle);
	//iso[Z][Z] = cos(angle);
	/*iso[X][X] = cos(angle);
	iso[X][Y] = -sin(angle);
	iso[Z][X] = sin(angle);
	iso[Z][Y] = cos(angle);*/
	mul_tri_map(iso, map);
	//v3listmul(iso, map->points, map->length);
}
