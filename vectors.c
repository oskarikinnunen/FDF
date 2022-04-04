/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <eino.oskari.kinnunen@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:47:59 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/04 19:32:47 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	*v3new(float x, float y, float z)
{
	float	*v3;

	v3 = (float *)malloc(sizeof(float) * 3);
	v3[X] = x;
	v3[Y] = y;
	v3[Z] = z;
	return (v3);
}

void	v3add(float *v3, float *add)
{
	v3[X] += add[X];
	v3[Y] += add[Y];
	v3[Z] += add[Z];
}

void	v3mul(float matrix[3][3], float *v3)
{
	float	t[3];
	int		index;

	index = X;
	while (index <= Z)
	{
		t[index]
			= (v3[X] * matrix[0][index])
			+ (v3[Y] * matrix[1][index])
			+ (v3[Z] * matrix[2][index]);
		index++;
	}
	v3[X] = t[X];
	v3[Y] = t[Y];
	v3[Z] = t[Z];
}

void	v3listmul(float matrix[3][3], float **v3s, int len)
{
	while (len >= 0)
		v3mul(matrix, v3s[len--]);
}

void	v3listadd(float **v3s, float *add, int len)
{
	while (len >= 0)
		v3add(v3s[len--], add);
}
