/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 04:53:43 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/19 00:00:57 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_with_size_matrix(t_map *map)
{
	static float	scale[3][3] = {
	{22, 0, 0},
	{0, 22, 0},
	{0, 0, 3}
	};

	v3listmul(scale, map->points, map->length);
}

void	scale_with_y_matrix(t_map *map, double angle)
{
	static float	iso[3][3] = {
	{1, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
	};

	angle = angle * 3.14 / 180;
	angle = asin(tan(angle));
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

	angle = angle * 3.14 / 180;
	iso[X][X] = cos(angle);
	iso[X][Y] = -sin(angle);
	iso[Z][X] = sin(angle);
	iso[Z][Y] = cos(angle);
	v3listmul(iso, map->points, map->length);
	/*i = 0;
	while (i < 3)
	{
		ft_memcpy(&(matrix[i]), &(iso[i]), sizeof(float) * 3);
		i++;
	}*/
	//v3
	//return (matrix);
}
