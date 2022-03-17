/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 04:53:43 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/17 10:05:03 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	setmatrix_scale(float matrix[3][3])
{
	static float	scale[3][3] = {
	{22, 0, 0},
	{0, 22, 0},
	{0, 0, 3}
	};
	int				i;

	i = 0;
	while (i < 3)
	{
		ft_memcpy(&(matrix[i]), &(scale[i]), sizeof(float) * 3);
		i++;
	}
}

void	setmatrix_iso_x(float matrix[3][3], double angle)
{
	static float	iso[3][3] = {
	{1, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
	};
	int				i;

	angle = angle * 3.14 / 180;
	angle = asin(tan(angle));
	iso[Y][Y] = cos(angle);
	iso[Y][Z] = sin(angle);
	iso[Z][Y] = -sin(angle);
	iso[Z][Z] = cos(angle);
	i = 0;
	while (i < 3)
	{
		ft_memcpy(&(matrix[i]), &(iso[i]), sizeof(float) * 3);
		i++;
	}
}

void	setmatrix_iso_y(float matrix[3][3], double angle)
{
	static float	iso[3][3] = {
	{0, 0, 0},
	{0, 1, 0},
	{0, 0, 0}
	};
	int				i;

	angle = angle * 3.14 / 180;
	iso[X][X] = cos(angle);
	iso[X][Z] = -sin(angle);
	iso[Z][X] = sin(angle);
	iso[Z][Z] = cos(angle);
	i = 0;
	while (i < 3)
	{
		ft_memcpy(&(matrix[i]), &(iso[i]), sizeof(float) * 3);
		i++;
	}
}
